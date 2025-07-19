#include "logging.h"
#include "flanterm_backends/fb.h"


struct flanterm_context* init_console(struct limine_framebuffer *framebuffer) {
	uint32_t *fb_ptr = framebuffer->address;
	struct flanterm_context *ft_ctx = flanterm_fb_init(
        NULL,
        NULL,
        fb_ptr, framebuffer->width, framebuffer->height, framebuffer->pitch,
        framebuffer->red_mask_size, framebuffer->red_mask_shift,
        framebuffer->green_mask_size, framebuffer->green_mask_shift,
        framebuffer->blue_mask_size, framebuffer->blue_mask_shift,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        0, 0,
        0
    );
	return ft_ctx;
}