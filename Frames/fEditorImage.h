//---------------------------------------------------------------------------
#ifndef fEditorImageH
#define fEditorImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>
#include "LMDDckSite.hpp"
#include "Project/ImageDocuments.h"
#include "Messaging/Event.h"
#include "Graphics/Image.h"
//---------------------------------------------------------------------------
class TfrmEditorImage : public TFrame
{
__published:    // IDE-managed Components
    TPanel *panToolOptions;
    TPanel *panContainer;
    TActionList *tbrActions;
    TImageList *tbrImages;
    TAction *actSelect;
    TAction *actPencil;
    TAction *actFill;
    TAction *actSprayBrush;
    TAction *actEraser;
    TAction *actLine;
    TAction *actShape;
    TPopupActionBar *popTools;
    TMenuItem *mnuSelect;
    TMenuItem *mnuText;
    TMenuItem *mnuBrush;
    TMenuItem *mnuLine;
    TMenuItem *mnuShapes;
    TMenuItem *mnuDropper;
    TMenuItem *mnuSprayBrush;
    TMenuItem *mnuFill;
    TAction *actGridPixel;
    TAction *actGridCharacter;
    TPanel *panToolbar;
    TToolBar *tbrShiftRotates;
    TToolButton *btnRotateLeft;
    TToolButton *btnRotateRight;
    TToolButton *btnRotateDown;
    TToolButton *btnRotateUp;
    TToolButton *btnRotateLeft90;
    TToolButton *btnRotateRight90;
    TToolButton *btnFlipHorizontal;
    TToolButton *btnFlipVertical;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnText;
    TToolButton *btnPencil;
    TToolButton *btnLine;
    TToolButton *btnShape;
    TToolButton *btnDropper;
    TToolButton *btnSprayBrush;
    TToolButton *btnFill;
    TAction *actText;
    TAction *actDropper;
    TPanel *panSplitter1;
    TPanel *panSplitter2;
    TPanel *panSplitter3;
    TToolBar *tbrMono;
    TToolButton *btnMonoOff;
    TToolButton *btnMonoOn;
    TPanel *panSplitter4;
    TToolBar *tbrGrids;
    TToolButton *btnGridCharacter;
    TToolButton *btnGridPixel;
    TStatusBar *barStatus;
    TPanel *panFrames;
    TAction *actRotateLeft;
    TAction *actRotateRight;
    TAction *actRotateUp;
    TAction *actRotateDown;
    TAction *actFlipVertical;
    TAction *actFlipHorizontal;
    TAction *actRotateLeft90;
    TAction *actRotateRight90;
    TAction *actMonoOn;
    TAction *actMonoOff;
    TScrollBox *sbxView;
    TAction *actBrush;
    TToolButton *btnBrush;
    TToolButton *btnEraser;
    TMenuItem *mnuEraser;
    TButton *btnTool;
    TPanel *panEditorContainer;
    TPanel *panViewFrame;
    TImage *imgEditor;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TScrollBox *ScrollBox1;
    TImage *Image1;
    TPanel *Panel1;
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actBrushExecute(TObject *Sender);
    void __fastcall actFillExecute(TObject *Sender);
    void __fastcall actSprayBrushExecute(TObject *Sender);
    void __fastcall actEraserExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actGridPixelExecute(TObject *Sender);
    void __fastcall actGridCharacterExecute(TObject *Sender);
    void __fastcall actTextExecute(TObject *Sender);
    void __fastcall actDropperExecute(TObject *Sender);
    void __fastcall FrameEndDock(TObject *Sender, TObject *Target, int X, int Y);
    void __fastcall actRotateLeftExecute(TObject *Sender);
    void __fastcall actRotateRightExecute(TObject *Sender);
    void __fastcall actRotateUpExecute(TObject *Sender);
    void __fastcall actRotateDownExecute(TObject *Sender);
    void __fastcall actFlipVerticalExecute(TObject *Sender);
    void __fastcall actFlipHorizontalExecute(TObject *Sender);
    void __fastcall actRotateLeft90Execute(TObject *Sender);
    void __fastcall actRotateRight90Execute(TObject *Sender);
    void __fastcall actMonoOnExecute(TObject *Sender);
    void __fastcall actMonoOffExecute(TObject *Sender);
    void __fastcall panEditorContainerClick(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall sbxViewResize(TObject *Sender);
private:    // User declarations
    typedef std::vector<std::unique_ptr<Agdx::Image>> ImageList;

    ImageDocument*              m_Image;            // the image document we are editing
    ImageList                   m_Frames;           // the image documents frames as bitmap images
    std::map<String, TAction*>  m_ActionMap;
    int                         m_Magnification;
    int                         m_SelectedFrame;    // the frame we are editing

    void            __fastcall  SetDocument(Document* document);
    void            __fastcall  OnEvent(const Event& event);
    bool            __fastcall  IsActive() const;
    void            __fastcall  DrawGrids();
    void            __fastcall  RefreshView();

public:        // User declarations
                    __fastcall  TfrmEditorImage(TComponent* Owner);
                    __fastcall ~TfrmEditorImage();
     static  TFrame* __fastcall Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorImage(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property  ImageDocument*  Image = { read = m_Image, write = m_Image };
};
//---------------------------------------------------------------------------
#endif
