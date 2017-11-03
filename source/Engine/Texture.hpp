#pragma once

#include "Engine/Exception.hpp"
#include "Engine/Types.hpp"

#include <GL/gl3w.h>

namespace le {

class Texture {
public:
    Texture();
    Texture(Texture& texture);
    Texture(const char* path);

    GLuint& Id = m_Id;

    uint& Width = m_Width;
    uint& Height = m_Height;

    Texture& operator=(const Texture& other);

    enum class Error { UNKNOWN, FILE_NOT_FOUND, BAD_FILE, UNSUPPORTED_FILE_TYPE };

    class TextureException : public Exception {
    public:
        TextureException(Error type) : Exception(), ErrorType(type) {}
        TextureException(Error type, const char* message) : Exception(message), ErrorType(type) {}

        Error ErrorType = Error::UNKNOWN;
    };

private:
    static bool defaultInitialized;
    static uint defaultId;

    uint m_Id;

    uint m_Width;
    uint m_Height;

    struct DDS_PIXELFORMAT {
        uint size;
        uint flags;
        uint fourCC;
        uint RGBBitCount;
        uint RBitMask;
        uint GBitMask;
        uint BBitMask;
        uint ABitMask;
    };

    struct DDS_HEADER {
        uint size;
        uint flags;
        uint height;
        uint width;
        uint pitchOrLinearSize;
        uint depth;
        uint mipMapCount;
        uint _dwReserved1[11];
        DDS_PIXELFORMAT pf;
        uint caps;
        uint caps2;
        uint caps3;
        uint caps4;
        uint _dwReserved2;
    };

    void ddsLoadUncompressed(DDS_HEADER header, std::ifstream* fs);
    void ddsLoadCompressed(DDS_HEADER header, std::ifstream* fs);
};
}
