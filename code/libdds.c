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

#include <libdds.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* SunOS 4.1.3_U1 has no SEEK_* defines */
#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif

/* Load DDS file
 */
dds_uint dds_load (const char* filename, DDSTextureInfo* texture) {
    if (texture == NULL) {
        printf ("dds_load: invalid surface!\n");
    }
    FILE* file;
    char magic[4];
    dds_long bufferSize, curr, end;

    file = fopen (filename, "rb");
    if (!file) {
        return DDS_CANNOT_OPEN;
    }

    /* Read magic number */
    fread (&magic, sizeof (char), 4, file);

    if (strncmp (magic, "DDS ", 4) != 0) {
        texture->ok = DDS_FALSE;
        fclose (file);
        return DDS_INVALID_FILE;
    }

    /* Get surface descriptor */
    fread (&texture->surface, sizeof (DDSurfaceDesc), 1, file);

    /* Calculate pixel data size */
    curr = ftell (file);
    fseek (file, 0, SEEK_END);
    end = ftell (file);
    fseek (file, curr, SEEK_SET);
    bufferSize = end - curr;
    texture->buffer_size = bufferSize;

    /* Read pixel data (with mipmaps) */
    texture->texels = (dds_ubyte*)malloc (bufferSize * sizeof (dds_ubyte));
    fread (texture->texels, sizeof (dds_ubyte), bufferSize, file);

    texture->ok = DDS_TRUE;

    fclose (file);
    return DDS_OK;
}

/* Free DDS texture
 */
void dds_free (DDSTextureInfo* texinfo) {
    if (texinfo->ok) {
        free (texinfo->texels);
        texinfo->texels = NULL;
        texinfo->ok = DDS_FALSE;
    }
}

/* Get error description
 */
const char* dds_error_string (int err) {
    switch (err) {
        case DDS_OK:
            return "No error";
        case DDS_CANNOT_OPEN:
            return "Cannot open image file";
        case DDS_INVALID_FILE:
            return "Given file does not appear to be a valid DDS file";
        case DDS_BAD_COMPRESSION:
            return "Given file does not appear to be compressed with DXT1, DXT3 or DXT5";
        case DDS_NO_GL_SUPPORT:
            return "Seems that OpenGL has no \"glCompressedTexImage2D\" extension";
        case DDS_CANNOT_WRITE_FILE:
            return "Cannot write file";
        case DDS_BAD_TEXINFO:
            return "Bad texture given";
        default:
            return "Unknown error";
    }
}

/* Free raw pixel data
 */
void dds_free_raw (DDSRawPixelData* data) {
    if (data->ok) {
        free (data->texels);
        data->ok = DDS_FALSE;
    }
}

/* Write DDS file
 */
dds_uint dds_write (const char* filename, const DDSTextureInfo* texinfo) {
    if (!texinfo->ok) {
        return DDS_BAD_TEXINFO;
    }

    FILE* file = fopen (filename, "wb");
    if (!file) {
        return DDS_CANNOT_WRITE_FILE;
    }

    /* Write magic number */
    fwrite ("DDS ", sizeof (char), 4, file);

    /* Write surface desc */
    fwrite (&texinfo->surface, sizeof (DDSurfaceDesc), 1, file);

    /* Write compressed texels */
    fwrite (texinfo->texels, sizeof (dds_ubyte), texinfo->buffer_size, file);

    fclose (file);
    return DDS_OK;
}
