#include "Engine/Texture.hpp"

#include <fstream>

const uint DDS_MAGIC = 0x20534444;

const uint DDSD_PITCH = 0x8;
const uint DDPF_RGB = 0x40;
const uint DDSD_LINEARSIZE = 0x80000;
const uint DDPF_FOURCC = 0x4;

const uint DDS_DXT1 = 0x31545844;
const uint DDS_DXT3 = 0x33545844;
const uint DDS_DXT5 = 0x35545844;

template <typename T> inline T get(byte* binary, int position) {
    return *(T*) &(binary[position]);
}

namespace le {

bool Texture::defaultInitialized = false;
uint Texture::defaultId = 0;

Texture::Texture() {
    if (!defaultInitialized) {
        glGenTextures(1, &defaultId);
        glBindTexture(GL_TEXTURE_2D, defaultId);
        byte defaultTexture[4]{255, 255, 255, 255};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, defaultTexture);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    m_Id = defaultId;
}

Texture::Texture(Texture& texture) {
    m_Id = texture.Id;
    m_Width = texture.Width;
    m_Height = texture.m_Height;
}

Texture::Texture(const char* path) {
    std::ifstream fs;
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fs = std::ifstream(path, std::ios::binary);

    if (fs.fail()) {
        throw TextureException(Error::FILE_NOT_FOUND);
    }

    byte headerBuffer[128];
    fs.read(reinterpret_cast<char*>(&headerBuffer), 128);

    if (get<uint>(headerBuffer, 0) != DDS_MAGIC) {
        throw TextureException(Error::UNSUPPORTED_FILE_TYPE, "Supported only DirectDraw Surface (DDS) files");
    }

    DDS_HEADER header = get<DDS_HEADER>(headerBuffer, 4);

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    if (header.flags & DDSD_PITCH && header.pf.flags & DDPF_RGB) {
        ddsLoadUncompressed(header, &fs);
    }
    else if (header.flags & DDSD_LINEARSIZE && header.pf.flags & DDPF_FOURCC) {
        ddsLoadCompressed(header, &fs);
    }
    else {
        throw TextureException(Error::BAD_FILE);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    fs.close();
}

Texture& Texture::operator=(const Texture& other) {
    if (this != &other) {
        m_Id = other.Id;
        m_Width = other.Width;
        m_Height = other.m_Height;
    }

    return *this;
}

void Texture::ddsLoadUncompressed(DDS_HEADER h, std::ifstream* fs) {
    if (!(h.pf.RGBBitCount == 32 && h.pf.ABitMask == 0xFF000000)) {
        throw TextureException(Error::UNSUPPORTED_FILE_TYPE, "Supported only A8R8G8B8 uncompressed textures");
    }

    byte* buffer;

    uint width = h.width, height = h.height;
    for (uint level = 0; level < h.mipMapCount; level++) {
        uint size = width * height * 4;

        buffer = new byte[size];
        fs->read(reinterpret_cast<char*>(buffer), size);

        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        width /= 2;
        height /= 2;

        delete[] buffer;
    }
}

void Texture::ddsLoadCompressed(DDS_HEADER h, std::ifstream* fs) {
    byte* buffer;
    uint bufferSize = h.mipMapCount > 1 ? h.pitchOrLinearSize * 2 : h.pitchOrLinearSize;

    buffer = new byte[bufferSize];
    fs->read(reinterpret_cast<char*>(buffer), bufferSize);

    GLenum compression;
    switch (h.pf.fourCC) {
    case DDS_DXT1:
        compression = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case DDS_DXT3:
        compression = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case DDS_DXT5:
        compression = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    }

    uint blockSize = (compression == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    uint offset = 0, width = h.width, height = h.height;
    for (uint level = 0; level < h.mipMapCount && (h.width || h.height); level++) {
        uint size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;

        glCompressedTexImage2D(GL_TEXTURE_2D, level, compression, width, height, 0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;
    }

    delete[] buffer;
}
}
