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
#ifndef _LIBDDS_OPENGL_H
#define	_LIBDDS_OPENGL_H

#include <dds_types.h>

#ifdef	__cplusplus
extern "C" {
#endif

    /** OpenGL texture info */
    typedef struct _DDS_GL_TextureInfo {
        dds_int     width;
        dds_int     height;
        dds_uint    format;
        dds_int     internal_format;
        dds_uint    id;
        dds_uint    num_mipmaps;
    } DDS_GL_TextureInfo;

    /** Load OpenGL texture
     * @par filename Texture filename
     * @par texture Texture to load to
     * @return Error code
     */
    DDS_API dds_uint DDS_APIENTRY ddsGL_load (const char* filename,
            DDS_GL_TextureInfo* texture);

    /** Release OpenGL texture
     * @par texture Texture to release
     */
    DDS_API void DDS_APIENTRY ddsGL_free (DDS_GL_TextureInfo* texture);

#ifdef	__cplusplus
}
#endif

#endif	/* _LIBDDS_OPENGL_H */

