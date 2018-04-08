//---------------------------------------------------------------------------
#ifndef GraphicsTypesH
#define GraphicsTypesH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
// btBitmap         the buffer represents a bitmap of pixels; from 1 bit (monochrome) to 2,4 or 8 bits (paletted colour).
// btAttribute      the buffer represents the color values for the bitmap of pixels. Usually in 8x8 or 8x1 grouping.
// btCharacterMap   the buffer represents a character display similar to the MSX
enum BufferType { btBitmap = 0, btAttribute = 1, btCharacterMap = 2, btInvalid = -1 };
enum ImageTypes { itObject, itSprite, itTile, itCharacterSet, itEnd };
// a typical byte buffer
typedef std::vector<unsigned char>  UnsignedCharBuffer;
#endif // GraphicsTypesH
