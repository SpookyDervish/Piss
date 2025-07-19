#pragma once
#include <stdint.h>

void gdt_set_gate(int32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
void gdt_install();
void gdt_flush();
void tss_flush();