#include "screen.h"
#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include "util/ssfn.h"

// TODO: if i ever get memory management going, ill use the coloured ANSII mode, but i need realloc and memset and that kinda thing.

void init_console(struct limine_framebuffer *framebuffer) {
	// load all our framebuffer data into the ssfn_dst data idk
	//ssfn_src = &_binary_console_sfn_start; // TODO: link this somehow
	ssfn_dst.ptr = framebuffer->address;
	ssfn_dst.p = framebuffer->pitch;
	ssfn_dst.w = framebuffer->width;
	ssfn_dst.h = framebuffer->height;
	ssfn_dst.x = 0;
	ssfn_dst.y = 0;
}

void draw_char(uint32_t c) {
	ssfn_putc(c);
}