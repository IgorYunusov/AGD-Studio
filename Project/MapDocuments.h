//---------------------------------------------------------------------------
#ifndef MapDocumentsH
#define MapDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Project/ImageDocuments.h"
//---------------------------------------------------------------------------
class TiledScreenDocument : public Document
{
public:

private:
    struct TileInfo
    {
        int X;
        int Y;
        TileDocument* Tile;
    };
    typedef std::vector<TileInfo> TileInfoList;

    TileInfoList                    m_Tiles;

public:
                        __fastcall  TiledScreenDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledScreenDocument(name); };

    virtual void        __fastcall  Save();

__published:
};
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
public:

private:
    std::vector<int>                m_Map;          // indexes into m_Screens
  std::vector<TiledScreenDocument*> m_Screens;

            int                     m_Across;
            int                     m_Down;
            int                     m_StartLocationX;
            int                     m_StartLocationY;
            int                     m_WindowWidth;
            int                     m_WindowHeight;
            TColor                  m_BackgroundColor;

public:
                        __fastcall  TiledMapDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledMapDocument(name); };

            void        __fastcall  Save();

__published:
    __property          int         Across          = { read = m_Across         , write = m_Across          };
    __property          int         Down            = { read = m_Down           , write = m_Down            };
    __property          int         StartLocationX  = { read = m_StartLocationX , write = m_StartLocationX  };
    __property          int         StartLocationY  = { read = m_StartLocationY , write = m_StartLocationY  };
    __property          int         WindowWidth     = { read = m_WindowWidth    , write = m_WindowWidth     };
    __property          int         WindowHeight    = { read = m_WindowHeight   , write = m_WindowHeight    };
    __property          TColor      BackgroundColor = { read = m_BackgroundColor, write = m_BackgroundColor };
};
//---------------------------------------------------------------------------
#endif
