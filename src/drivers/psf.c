#include "psf.h"
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>


extern const struct PSF_font _binary_assets_zap_ext_vga16_psf_start;
const struct PSF_font *default_font = &_binary_assets_zap_ext_vga16_psf_start;

void putc(char c, struct limine_framebuffer *framebuffer, uint32_t fg, uint32_t bg, int col, int row) {
	const uint8_t *glyph = (const uint8_t *)default_font + default_font->headersize +
                           (default_font->bytesperglyph * (ptrdiff_t)c);

	size_t index = (row * default_font->height * framebuffer->pitch) + (col * default_font->width);
	volatile uint32_t *fb_ptr = framebuffer->address;

	uint32_t bytesperline = default_font->width / 8;

	for (size_t y = 0; y < default_font->height; ++y)
    {
        for (size_t x = 0; x < default_font->width; ++x)
        {
            const uint8_t current_byte = glyph[x / 8];
            const uint8_t highest_bit = 0x80U;
            const uint8_t current_bitmask = highest_bit >> (x & 7U);
			
			// we're resorting to colours bbaabyyyyy
            fb_ptr[index+x] = default_font->width*default_font->height;//(current_byte & current_bitmask) ? fg : bg;
        }
        glyph += bytesperline;
        index += framebuffer->pitch;
    }
}