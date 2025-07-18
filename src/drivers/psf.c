#include "psf.h"
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>


extern const struct PSF_font _binary_assets_ZAP_psf_start;
const struct PSF_font *default_font = &_binary_assets_ZAP_psf_start;

void putc(char c, struct limine_framebuffer *framebuffer, uint32_t fg, uint32_t bg, int col, int row) {
	volatile uint32_t *fb_ptr = framebuffer->address;

    if (default_font->magic == PSF1_MAGIC) {
		for (int y = 0; y < framebuffer->height; y++) {
			for (int x = 0; x < framebuffer->width; x++) {
				fb_ptr[framebuffer->width*y + x] = 0x00FF00;
			}
		}
	} else {
		for (int y = 0; y < framebuffer->height; y++) {
			for (int x = 0; x < framebuffer->width; x++) {
				fb_ptr[framebuffer->width*y + x] = default_font->magic;
			}
		}
	}
}