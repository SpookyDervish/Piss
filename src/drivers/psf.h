#pragma once
#include <stdint.h>
#include "limine.h"


#define PSF1_MAGIC 0x3604

typedef struct {
    uint8_t magic[2]; // Magic bytes for identification.
    uint8_t fontMode; // PSF font mode.
    uint8_t characterSize; // PSF character size.
} PSF1_Header;

struct PSF_font {
    uint32_t magic;         /* magic bytes to identify PSF */
    uint32_t version;       /* zero */
    uint32_t headersize;    /* offset of bitmaps in file, 32 */
    uint32_t flags;         /* 0 if there's no unicode table */
    uint32_t numglyph;      /* number of glyphs */
    uint32_t bytesperglyph; /* size of each glyph */
    uint32_t height;        /* height in pixels */
    uint32_t width;         /* width in pixels */
};

void putc(char c, struct limine_framebuffer *framebuffer, uint32_t fg, uint32_t bg, int col, int row);