/*---------------------------------------------------------------------------

   pngquant:  RGBA -> RGBA-palette quantization program             rwpng.h

  ---------------------------------------------------------------------------

      Copyright (c) 1998-2000 Greg Roelofs.  All rights reserved.

      This software is provided "as is," without warranty of any kind,
      express or implied.  In no event shall the author or contributors
      be held liable for any damages arising in any way from the use of
      this software.

      Permission is granted to anyone to use this software for any purpose,
      including commercial applications, and to alter it and redistribute
      it freely, subject to the following restrictions:

      1. Redistributions of source code must retain the above copyright
         notice, disclaimer, and this list of conditions.
      2. Redistributions in binary form must reproduce the above copyright
         notice, disclaimer, and this list of conditions in the documenta-
         tion and/or other materials provided with the distribution.
      3. All advertising materials mentioning features or use of this
         software must display the following acknowledgment:

            This product includes software developed by Greg Roelofs
            and contributors for the book, "PNG: The Definitive Guide,"
            published by O'Reilly and Associates.

  ---------------------------------------------------------------------------*/

#include "png.h"    /* libpng header; includes zlib.h */

#ifndef TRUE
#  define TRUE 1
#  define FALSE 0
#endif

typedef enum {
    SUCCESS = 0,
    READ_ERROR = 2,
    TOO_MANY_COLORS = 5,
    NOT_OVERWRITING_ERROR = 15,
    CANT_WRITE_ERROR = 16,
    OUT_OF_MEMORY_ERROR = 17,
    WRONG_ARCHITECTURE = 18, // Missing SSE3
    PNG_OUT_OF_MEMORY_ERROR = 24,
    INIT_OUT_OF_MEMORY_ERROR = 34,
    BAD_SIGNATURE_ERROR = 21,
    LIBPNG_FATAL_ERROR = 25,
    LIBPNG_INIT_ERROR = 35,
    LIBPNG_WRITE_ERROR = 55,
    LIBPNG_WRITE_WHOLE_ERROR = 45,

    INVALID_ARGUMENT = 4,
    MISSING_ARGUMENT = 1,
} pngquant_error;

typedef struct {
    jmp_buf jmpbuf;
    png_uint_32 width;
    png_uint_32 height;
    png_uint_32 rowbytes;
    double gamma;
    int interlaced;
    unsigned char *rgba_data;
    unsigned char **row_pointers;
} read_info;

typedef struct {
    jmp_buf jmpbuf;
    void *png_ptr;
    void *info_ptr;
    png_uint_32 width;
    png_uint_32 height;
    double gamma;
    int interlaced;
    int num_palette;
    int num_trans;
    png_color palette[256];
    unsigned char trans[256];
    unsigned char *indexed_data;
    unsigned char **row_pointers;
} write_info;

typedef union {
    jmp_buf jmpbuf;
    read_info read;
    write_info write;
} read_or_write_info;

/* prototypes for public functions in rwpng.c */

void rwpng_version_info(FILE *fp);

pngquant_error rwpng_read_image(FILE *infile, read_info *mainprog_ptr);

pngquant_error rwpng_write_image_init(FILE *outfile, write_info *mainprog_ptr);

pngquant_error rwpng_write_image_whole(write_info *mainprog_ptr);

int rwpng_write_image_row(write_info *mainprog_ptr);

int rwpng_write_image_finish(write_info *mainprog_ptr);
