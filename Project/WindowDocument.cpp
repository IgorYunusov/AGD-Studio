//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Project/WindowDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall WindowDocument::WindowDocument(const String& name)
: Document(name)
{
    m_Type = "Game";
    m_SubType = "Window";
    m_Extension = "json";
    m_Folder = "Game\\Window";
    RegisterProperty("Left", "Position", "The start X position of the window");
    RegisterProperty("Top", "Position", "The start Y position of the window");
    RegisterProperty("Right", "Position", "The end X position of the window");
    RegisterProperty("Bottom", "Position", "The end Y position of the window");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the image");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the image");
    // json loading properties
    m_PropertyMap["Window.Left"] = &m_Rect.Left;
    m_PropertyMap["Window.Top"] = &m_Rect.Top;
    m_PropertyMap["Window.Right"] = &m_Rect.Right;
    m_PropertyMap["Window.Bottom"] = &m_Rect.Bottom;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall WindowDocument::DoSave()
{
    Push("Window");
        Write("Left", m_Rect.Left);
        Write("Top", m_Rect.Top);
        Write("Right", m_Rect.Right);
        Write("Bottom", m_Rect.Bottom);
    Pop();  // window
}
//---------------------------------------------------------------------------
int __fastcall WindowDocument::Get(int index)
{
    switch (index)
    {
        case 0: return m_Rect.Left; break;
        case 1: return m_Rect.Top; break;
        case 2: return m_Rect.Right; break;
        case 3: return m_Rect.Bottom; break;
        case 4: return m_Rect.Width(); break;
        case 5: return m_Rect.Height(); break;
    }
}
//---------------------------------------------------------------------------

