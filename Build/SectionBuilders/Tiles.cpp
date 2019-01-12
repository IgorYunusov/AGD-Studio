//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Tiles.h"
#include "Project/DocumentManager.h"
#include "Project/ImageDocuments.h"
#include "Graphics/GraphicsMode.h"
#include "Graphics/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const String BlockTypes[] = { "Empty", "Platform", "Wall", "Ladder", "Fodder", "Deadly", "Custom" };
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Tiles::Tiles()
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Tiles::~Tiles()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Tiles::Execute()
{
    const auto& dm = theDocumentManager;
    DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
        auto tile = dynamic_cast<TileDocument*>(image);
        if (tile != nullptr)
        {
            String line = "DEFINEBLOCK ";
            line += BlockTypes[StrToInt(tile->GetLayer("blocktype"))];
            line += " ";
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Agdx::Image>(tile, gm);
            image->ChangeFrame(0);
            auto data = image->GetExportNativeFormat();
            // export the machine graphics data
            for (auto byte : data)
            {
                line += IntToStr(byte) + " ";
            }
            AddLine(line);
            LineBreak();
        }
    }

    // no tiles is ok
    Success();
}
//---------------------------------------------------------------------------

