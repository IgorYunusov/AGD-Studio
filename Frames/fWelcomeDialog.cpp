//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fWelcomeDialog.h"
#include "ProjectManager.h"
#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmWelcomeDialog::TfrmWelcomeDialog(TComponent* Owner)
: TFrame(Owner)
{
    if (cmbThemes->Items->Count == 0)
    {
        auto sl = std::make_unique<TStringList>();
        for (auto i = 0; i < TStyleManager::StyleNames.Length; i++)
        {
            if (TStyleManager::StyleNames[i] != "Windows")
            {
                sl->Add(TStyleManager::StyleNames[i]);
            }
        }
        sl->Sort();
        const String style = appSettings.ActiveStyle;
        for (auto i = 0; i < sl->Count; i++)
        {
            cmbThemes->Items->Add(sl->Strings[i]);
            if (sl->Strings[i] == style)
            {
                cmbThemes->ItemIndex = cmbThemes->Items->Count - 1;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblStartNewProjectClick(TObject *Sender)
{
    panStartNew->Color = panButtons->Color;
    panStartNew->Visible = true;
    panButtons->Visible = false;
    edtName->Text = "";
    edtName->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::btnCreateClick(TObject *Sender)
{
    panButtons->Visible = true;
    panStartNew->Visible = false;
    auto button = dynamic_cast<TButton*>(Sender);
    if (button && button->ModalResult == mrOk)
    {
        theProjectManager.New(edtName->Text, cmbMachines->Items->Strings[cmbMachines->ItemIndex]);
        if (FOnDone) FOnDone(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblOpenExistingProjectClick(TObject *Sender)
{
    dlgOpen->InitialDir = System::Path::Projects;
    if (dlgOpen->Execute())
    {
        theProjectManager.Open(dlgOpen->FileName);
        if (FOnDone) FOnDone(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblImportAGDSnapshotClick(TObject *Sender)
{
    dlgImport->InitialDir = System::Path::Projects;
    if (dlgImport->Execute())
    {
        // TODO: Check the file is valid
        if (false)
        {
            // TODO: Implement Import
            auto name = System::File::NameWithExtension(dlgImport->FileName);
            theProjectManager.New(name, "ZX Spectrum 256x192 16 Colour");
            if (FOnDone) FOnDone(this);
        }
        else
        {
            MessageDlg("File is not a valid ZX Spectrum 48K Snapshot", mtError, TMsgDlgButtons() << mbOK, 0);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::SelectionPanelOnClick(TObject *Sender)
{
    TSelectionPanelFrame* panel = (TSelectionPanelFrame*)Sender;
    theProjectManager.Open(panel->Path);
    if (FOnDone) FOnDone(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::SelectionPanelOnRemoveClick(TObject *Sender)
{
    TSelectionPanelFrame* panel = (TSelectionPanelFrame*)Sender;
    theProjectManager.RemoveMostRecentlyUsedItem(panel->Name, panel->Path);
    RefreshMRUList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblStartNewProjectMouseEnter(TObject *Sender)
{
    ((TLabel*)Sender)->Font->Color = StyleServices()->GetStyleColor(scButtonHot);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblStartNewProjectMouseLeave(TObject *Sender)
{
    ((TLabel*)Sender)->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::cmbThemesChange(TObject *Sender)
{
    TStyleManager::SetStyle(cmbThemes->Text);
    appSettings.ActiveStyle = cmbThemes->Text;
    UpdateColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblConfigureClick(TObject *Sender)
{
    TPoint pt = lblConfigure->Parent->ClientToScreen(Point(lblConfigure->Left, lblConfigure->Top + lblConfigure->Height));
    popConfigure->Popup(pt.x, pt.y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::lblChangeThemeClick(TObject *Sender)
{
    cmbThemes->DroppedDown = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::Initialise()
{
    dynamic_cast<TForm*>(Parent)->Caption = "Welcome to AGDX Studio";
    RefreshMRUList();
    UpdateColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::UpdateColors()
{
    panMain->Color = StyleServices()->GetStyleColor(scGenericGradientBase);
    panRecentProjects->Color = StyleServices()->GetStyleColor(scGenericGradientEnd);
    lblStartNewProject->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblOpenExistingProject->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblImportAGDSnapshot->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblChangeTheme->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblConfigure->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    for (auto panel : m_MostRecentlyUsedItems) panel->UpdateControl();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::RefreshMRUList()
{
    m_MostRecentlyUsedItems.clear();
    for (const auto& item : theProjectManager.GetMostRecentlyUsedList())
    {
        NewMostRecentlyUsedItem(item.Name, item.Path);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::NewMostRecentlyUsedItem(const String& name, const String& path)
{
    auto spf = std::shared_ptr<TSelectionPanelFrame>(new TSelectionPanelFrame(this));
    m_MostRecentlyUsedItems.push_back(spf);
    spf->Parent = panRecentProjects;
    spf->Name = name;
    spf->Path = path;
    spf->OnSelectedClick = SelectionPanelOnClick;
    spf->OnRemoveClick = SelectionPanelOnRemoveClick;
    spf->Top = 1000;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::edtNameChange(TObject *Sender)
{
    auto isEmpty = edtName->Text.Trim() == "";
    auto file = ApplicationName + System::Path::Separator + edtName->Text;
    auto projectExists = System::File::Exists(file);
    lblFile->Caption = file;
    lblFile->Visible = !isEmpty;
    btnCreate->Enabled = !isEmpty && !projectExists;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWelcomeDialog::edtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == vkReturn && btnCreate->Enabled)
    {
        btnCreateClick(btnCreate);
    }
}
//---------------------------------------------------------------------------

