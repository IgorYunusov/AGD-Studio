//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "ElXTree.hpp"
#include "Document.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Document::Document(const String& name)
: m_Name(name)
, m_Type("No Type")
, m_SubType("No SubType")
, m_Extension("json")
, m_MultiDoc(false)
, m_Folder("Misc\\Files")
, m_TreeNode(nullptr)
, m_DockPanel(nullptr)
{
    m_Type = "Document";
    RegisterProperty("Name", "Details", "The name of the asset/document");
    RegisterProperty("Path", "Details", "The full path of the document");
    RegisterProperty("Name", "Details", "The name of the asset/document");
    RegisterProperty("Classification", "Details", "The classification of the document");
    m_PropertyMap[".Document.Name"] = &m_Name;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall Document::RegisterProperty(const String& property, const String& category, const String& info)
{
    m_PropertyInfo[property] = { category, info };
}
//---------------------------------------------------------------------------
const Document::TPropertyInfoMap& __fastcall Document::GetPropertyInfo() const
{
    return m_PropertyInfo;
}
//---------------------------------------------------------------------------
String __fastcall Document::GetPropertyInfo(const String& property) const
{
    auto info = m_PropertyInfo.find(property);
    if (info != m_PropertyInfo.end())
    {
        return info->second.info;
    }
    return "Invalid property";
}
//---------------------------------------------------------------------------
void __fastcall Document::SetName(String name)
{
    auto oldFile = GetFile();
    m_Name = name;
    if (m_TreeNode)
    {
        ((TElXTreeItem*)m_TreeNode)->Text = name;
    }
    // TODO: Rename file to new file name
    if (System::File::Exists(oldFile))
    {
        auto newFile = GetFile();
        System::File::Rename(oldFile, newFile);
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
String __fastcall Document::GetFile()
{
    // Documents/{project name}
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    // Documents/{project name}/{document name}
    file = System::File::Combine(file, m_Name);
    // Documents/{project name}/{document name}.{extension)
    file = System::File::ChangeExtension(file, m_Extension);
    return file;
}
//---------------------------------------------------------------------------
bool __fastcall Document::Load()
{
    if (m_File.Trim() == "")
    {
        m_File = GetFile();
    }
    // does it exist?
    if (System::File::Exists(m_File))
    {
        // yes, load it
        JsonFile::Load(m_File);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------

