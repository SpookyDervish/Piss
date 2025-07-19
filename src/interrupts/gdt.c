#include "gdt.h"

struct GDT_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));

struct GDT_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct GDT_entry gdt[5];
struct GDT_ptr gp;


void gdt_set_gate(int32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_install()
{
	/* Setup the GDT pointer and limit */
	gp.limit = (sizeof(struct GDT_entry) * 5) - 1;
	gp.base = (int)&gdt;

	gdt_set_gate(0, 0, 0, 0, 0); // null entry
	gdt_set_gate(1, 0, 0xFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0xCF);

	gdt_flush();
}