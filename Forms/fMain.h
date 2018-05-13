//---------------------------------------------------------------------------
#ifndef fMainH
#define fMainH
//- VCL ---------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
//- STL ---------------------------------------------------------------------
#include <memory>
//- APP ---------------------------------------------------------------------
#include "fWelcomeDialog.h"
#include "fImportDialog.h"
#include "fIDE.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:    // IDE-managed Components
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormActivate(TObject *Sender);
private:    // User declarations
    void __fastcall AppMessage(tagMSG &Msg, bool &Handled);
    void __fastcall OnIDEClose(TObject *Sender);
    void __fastcall OnWelcomeDone(TObject *Sender);
    void __fastcall OnImportDone(TObject *Sender);
    void __fastcall ShowWelcomeDialog();
    void __fastcall ShowImportDialog();
    void __fastcall ShowIDE();
    void __fastcall SaveSettings();

private:

    enum TFormView
    {
        fvNone,
        fvWelcomeDialog,
        fvImportDialog,
        fvGameIDE,
    };

    TFormView                           m_FormView;
    std::unique_ptr<TfrmWelcomeDialog>  m_WelcomeDialog;
    std::unique_ptr<TfrmImportDialog>   m_ImportDialog;
    std::unique_ptr<TfrmIDE>            m_IDEDialog;

public:        // User declaration
            __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
