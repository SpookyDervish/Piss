#pragma once
#include <stdint.h>
#include "limine.h"

void init_console(struct limine_framebuffer *framebuffer);
void draw_char(uint32_t c);