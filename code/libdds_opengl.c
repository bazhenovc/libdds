/*
 * libdds
 * Copyright (c) 2010 Cyril Bazhenov bazhenovc@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#include <libdds_opengl.h>
#include <libdds.h>

#include <GL/gl.h>
#include <GL/glext.h>
#include <stdlib.h>

#ifdef _WIN32
#include <wgl.h>
#else
#include <GL/glx.h>
#endif

PFNGLCOMPRESSEDTEXIMAGE2DARBPROC ddsglCompressedTexImage2D = NULL;

static int ddsgl_init () {
    if (ddsglCompressedTexImage2D) {
        return (1);
    }
#ifdef _WIN32
    ddsglCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) wglGetProcAddress ("glCompressedTexImage2DARB");
#else
    ddsglCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) glXGetProcAddress ((const dds_ubyte*) "glCompressedTexImage2DARB");
#endif
    return (ddsglCompressedTexImage2D != NULL);
}

dds_uint ddsGL_load (const char* filename, DDS_GL_TextureInfo* texture) {
    if (!ddsgl_init ()) {
        return DDS_NO_GL_SUPPORT;
    }
    DDSTextureInfo textureInfo;
    dds_int error = dds_load (filename, &textureInfo);
    if (error != DDS_OK) {
        return error;
    }
    texture->width = textureInfo.surface.width;
    texture->height = textureInfo.surface.height;
    texture->num_mipmaps = textureInfo.surface.mip_level;
    switch (textureInfo.surface.format.fourcc) {
        case DDS_FOURCC_DXT1:
            texture->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            texture->internal_format = 3;
            break;
        case DDS_FOURCC_DXT3:
            texture->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            texture->internal_format = 4;
            break;
        case DDS_FOURCC_DXT5:
            texture->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            texture->internal_format = 4;
            break;
        default:
            dds_free (&textureInfo);
            return DDS_BAD_COMPRESSION;
    }
    /* Generate new texture */
    glGenTextures (1, &texture->id);
    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, texture->id);
    /* Filtering */
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    size_t blockSize = texture->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16;
    size_t offset = 0;
    dds_uint mipWidth = texture->width,
            mipHeight = texture->height,
            mipSize;
    /* Upload mipmaps to video memory */
    size_t mip;
    for (mip = 0; mip < texture->num_mipmaps; mip++) {
        mipSize = ((mipWidth + 3) / 4) * ((mipHeight + 3) / 4) * blockSize;

        ddsglCompressedTexImage2D (GL_TEXTURE_2D, mip, texture->format,
                mipWidth, mipHeight, 0, mipSize,
                textureInfo.texels + offset);

        mipWidth = DDS_MAX (mipWidth >> 1, 1);
        mipHeight = DDS_MAX (mipHeight >> 1, 1);

        offset += mipSize;
    }
    dds_free (&textureInfo);
    glDisable (GL_TEXTURE_2D);
    return DDS_OK;
}

void ddsGL_free (DDS_GL_TextureInfo* texture) {
    if (texture->id) {
        glDeleteTextures (1, &texture->id);
    }
}
