//---------------------------------------------------------------------------
#ifndef DocumentH
#define DocumentH
//---------------------------------------------------------------------------
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
//---------------------------------------------------------------------------
#include <map>
#include <vector>
//---------------------------------------------------------------------------
// Inheritence map
// Document -> System::JsonFile -> TPersistent
// TPersistent is a Delphi class used by the property editor to extract
// published __property items from a class that can be then viewed/edited.
// JsonFile does not use TPersistent; but Document does.
// Delphi classes cannot use Multiple Inheritence; so JsonFile then needs to
// derive from TPersistent; since Document can't. But in the end this all
// works out nicely as technically a JsonFile file is persistent; it's just
// we aren't using Delphi's persistence.
//---------------------------------------------------------------------------
class Document : public System::JsonFile
{
public:
    struct TPropertyInfo
    {
        String  category;
        String  info;
    };
    typedef std::map<String,TPropertyInfo>  TPropertyInfoMap;
    TPropertyInfoMap::iterator              TPropertyInfoMapIt;

protected:
            String                  m_Name;
            String                  m_Type;
            String                  m_SubType;
            String                  m_Folder;
            bool                    m_MultiDoc;
            TPropertyInfoMap        m_PropertyInfo;
            void*                   m_TreeNode;
            void*                   m_DockPanel;

                                    // update the documents json content
    virtual void        __fastcall  Update() {};//= 0;
                                    // convert json data to document data
    virtual void        __fastcall  OnLoad() {};//= 0;

            void        __fastcall  RegisterProperty(const String& property, const String& category, const String& info);

public:
                        __fastcall  Document();
                        __fastcall  Document(const String& subType);

    static  Document*   __fastcall  Create()      { throw "Don't create this class";    }

            void        __fastcall  Save();
            bool        __fastcall  Load(const String& file);
const TPropertyInfoMap& __fastcall  GetPropertyInfo() const;
            String      __fastcall  GetPropertyInfo(const String& property) const;

    __property          String      Type        = { read = m_Type                   };
    __property          String      SubType     = { read = m_SubType                };
    __property          bool        IsMultiDoc  = { read = m_MultiDoc               };
    __property          void*       TreeNode    = { read = m_TreeNode, write = m_TreeNode };
    __property          void*       DockPanel   = { read = m_DockPanel, write = m_DockPanel };

__published:
    __property          String      Folder      = { read = m_Folder                     };
    __property          String      Name        = { read = m_Name   , write = m_Name    };
};
//---------------------------------------------------------------------------
typedef Document* (__fastcall *CreateDocumentFn)();
//---------------------------------------------------------------------------
#endif
