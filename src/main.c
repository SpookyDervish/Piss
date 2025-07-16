#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "gcc_methods.h"
#include "drivers/screen.h"
#include <limine.h>

// quick note about all limine requests:
// the requests should be defined as volatile to prevent the compiler
// from optimizing them out, as well as the "used" things. idfk, i'm
// just following the osdev wiki lmao

// Limine has several versions, atm, version 3 is the latest.
// check the spec here every so often to see if a new version
// comes out:
// https://github.com/limine-bootloader/limine-protocol/blob/trunk/PROTOCOL.md
//
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// define the start and end markers for the limine requests
// these can be moved anywhere, to any .c file as see fit
__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

// Halt and catch fire function.
static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.
void kmain(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    init_console(framebuffer);
    draw_char('H');

    // We're done, just hang...
    hcf();
}