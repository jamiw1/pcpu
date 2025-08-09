#include "include.h"
#include "mem.h"
#include "cpu.h"

int main(void) {
    cpu_t cpu;
    mem_t mem;

    mem_init(&mem);
    mem_write_byte(&mem, 0x0000, 0x50);
    mem_write_byte(&mem, 0x0001, 69);
    mem_write_byte(&mem, 0x0002, 0x15);

    mem_write_byte(&mem, 0x0045, 0x10);
    mem_write_byte(&mem, 0x0046, 5);
    mem_write_byte(&mem, 0x0047, 0x20);
    mem_write_byte(&mem, 0x0048, 3);
    mem_write_byte(&mem, 0x0049, 0x30);
    mem_write_byte(&mem, 0x004a, 9);
    mem_write_byte(&mem, 0x004b, 0x40);
    mem_write_byte(&mem, 0x004c, 5);
    mem_write_byte(&mem, 0x004d, 0x60);
    mem_write_byte(&mem, 0x004e, 2);

    cpu_reset(&cpu, &mem);
    
    cpu_exec(&cpu, 13, false);
    printf("%d", cpu.pc);

    return 0;
}