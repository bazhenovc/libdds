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
#ifndef _LIBDDS_H
#define	_LIBDDS_H

#include <dds_types.h>

#ifdef	__cplusplus
extern "C" {
#endif

    /** DirectDraw pixel format */
    typedef struct _DDPixelFormat {
        dds_uint    size;
        dds_uint    flags;
        dds_uint    fourcc;
        dds_uint    bpp;
        dds_uint    red_mask;
        dds_uint    green_mask;
        dds_uint    blue_mask;
        dds_uint    alpha_mask;
    } DDPixelFormat;

    /** DDS caps */
    typedef dds_uint DDSCaps[4];

    /** DirectDraw color key */
    typedef struct _DDColorKey {
        dds_uint    low;
        dds_uint    high;
    } DDColorKey;

    /** DirectDraw surface descriptor */
    typedef struct _DDSurfaceDesc {
        dds_uint    size;
        dds_uint    flags;
        dds_uint    height;
        dds_uint    width;
        dds_uint    pitch;
        dds_uint    depth;
        dds_uint    mip_level;
        dds_uint    alpha_bit_depth;
        dds_uint    __reserved;
        dds_uint    surface;
        DDColorKey  dest_overlay;
        DDColorKey  dest_blit;
        DDColorKey  src_overlay;
        DDColorKey  src_blit;
        DDPixelFormat format;
        DDSCaps     caps;
        dds_uint    texture_stage;
    } DDSurfaceDesc;

    /** DDS texture info */
    typedef struct _DDSTextureInfo {
        DDSurfaceDesc   surface;
        dds_ubyte*      texels;
        dds_long        buffer_size;
        dds_bool        ok;
    } DDSTextureInfo;

    /** Raw pixels */
    typedef struct _DDSRawPixelData {
        dds_uint        height;
        dds_uint        width;
        dds_ubyte*      texels;
        dds_bool        ok;
    } DDSRawPixelData;

    #define DDS_MAKE_FOURCC(ch0, ch1, ch2, ch3) \
        ((dds_uint)( \
        (((dds_uint)(dds_ubyte)(ch3) << 24) & 0xFF000000) | \
        (((dds_uint)(dds_ubyte)(ch2) << 16) & 0x00FF0000) | \
        (((dds_uint)(dds_ubyte)(ch1) <<  8) & 0x0000FF00) | \
         ((dds_uint)(dds_ubyte)(ch0)        & 0x000000FF) ))

    #define DDS_FOURCC_DXT1 DDS_MAKE_FOURCC('D', 'X', 'T', '1')
    #define DDS_FOURCC_DXT3 DDS_MAKE_FOURCC('D', 'X', 'T', '3')
    #define DDS_FOURCC_DXT5 DDS_MAKE_FOURCC('D', 'X', 'T', '5')
    #define DDS_FOURCC_BC4U DDS_MAKE_FOURCC('B', 'C', '4', 'U')
    #define DDS_FOURCC_BC4S DDS_MAKE_FOURCC('B', 'C', '4', 'S')
    #define DDS_FOURCC_BC5S DDS_MAKE_FOURCC('B', 'C', '5', 'S')

    /** Errors */
    #define DDS_OK                  0
    #define DDS_CANNOT_OPEN         1
    #define DDS_INVALID_FILE        2
    #define DDS_BAD_COMPRESSION     3
    #define DDS_NO_GL_SUPPORT       4
    #define DDS_CANNOT_WRITE_FILE   5
    #define DDS_BAD_TEXINFO         6

    /** Utils */
    #define DDS_MAX(a, b) (a > b ? a : b)
    #define DDS_MIN(a, b) (a > b ? b : a)

    /* =====================Load/Free========================= */

    /** Load DDS file
     * @par filename File name
     * @par texture Texture to load to
     * @return Error code
     */
    DDS_API dds_uint DDS_APIENTRY dds_load (const char* filename,
            DDSTextureInfo* texture);

    /** Free DDS file
     * @par texinfo DDS texture info
     */
    DDS_API void DDS_APIENTRY dds_free (DDSTextureInfo* texinfo);

    /** Get error string description
     * @par err Error code
     * @return Error description
     */
    DDS_API const char* DDS_APIENTRY dds_error_string (int err);

    /** Free raw pixel data
     * @par data Data to free
     */
    DDS_API void DDS_APIENTRY dds_free_raw (DDSRawPixelData* data);

    /* =====================Pack/Unpack======================= */

    /** Unpack DXT1 compressed texture to raw data
     * @par texinfo Packed texture info
     * @par pixels Pixel data to unpack to
     * @return Error code
     * TODO: implement
     */
    DDS_API dds_uint DDS_APIENTRY dds_dxt1_unpack (DDSTextureInfo* texinfo,
            DDSRawPixelData* pixels);

    /** Unpack DXT3 compressed texture to raw data
     * @par texinfo Packed texture info
     * @par pixels Pixel data to unpack to
     * @return Error code
     * TODO: implement
     */
    DDS_API dds_uint DDS_APIENTRY dds_dxt3_unpack (DDSTextureInfo* texinfo,
            DDSRawPixelData* pixels);

    /** Unpack DXT5 compressed texture to raw data
     * @par texinfo Packed texture info
     * @par pixels Pixel data to unpack to
     * @return Error code
     * TODO: implement
     */
    DDS_API dds_uint DDS_APIENTRY dds_dxt5_unpack (DDSTextureInfo* texinfo,
            DDSRawPixelData* pixels);

    /** Pack raw pixel data with DXT1
     * @par pixels Raw pixel data
     * @par texinfo Texture info
     * @return Error code
     * TODO: implement
     */
    DDS_API dds_uint DDS_APIENTRY dds_dxt1_pack (DDSRawPixelData* pixels,
            DDSTextureInfo* texinfo);

    /** Pack raw pixel data with DXT3
     * @par pixels Raw pixel data
     * @par texinfo Texture info
     * @return Error code
     * TODO: implement
     */
    DDS_API dds_uint DDS_APIENTRY dds_dxt3_pack (DDSRawPixelData* pixels,
            DDSTextureInfo* texinfo);

    /** Pack raw pixel data with DXT5
     * @par pixels Raw pixel data
     * @par texinfo Texture info
     * @return Error code
     * TODO: implement
     */
    DDS_API dds_uint DDS_APIENTRY dds_dxt5_pack (DDSRawPixelData* pixels,
            DDSTextureInfo* texinfo);

    /* =====================Write============================= */

    /** Write DDS texture file
     * @par filename File name
     * @par texinfo Texture info to write
     * @return Error code
     */
    DDS_API dds_uint DDS_APIENTRY dds_write (const char* filename,
            const DDSTextureInfo* texinfo);

#ifdef	__cplusplus
}
#endif

#endif

