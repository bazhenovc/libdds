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
#ifndef _DDS_TYPES_H
#define	_DDS_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef int             dds_int;
    typedef unsigned int    dds_uint;
    typedef char            dds_byte;
    typedef unsigned char   dds_ubyte;
    typedef long            dds_long;
    typedef unsigned long   dds_ulong;
    typedef void            dds_void;
    typedef void*           dds_ptr;
    typedef enum _dds_bool {
        DDS_FALSE = 0,
        DDS_TRUE
    } dds_bool;

    #ifdef _WIN32
    #define DDS_API      __declspec(dllexport)
    #define DDS_APIENTRY __cdecl
    #else
    #define DDS_API extern
    #define DDS_APIENTRY
    #endif

#ifdef	__cplusplus
}
#endif

#endif	/* _DDS_TYPES_H */

