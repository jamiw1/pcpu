#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ZERO_FLAG_MASK (1 << 0b00000001)
#define CARRY_FLAG_MASK (1 << 0b00000010)
#define OVERFLOW_FLAG_MASK (1 << 0b00000100)
#define SIGN_FLAG_MASK (1 << 0b00001000)

typedef uint8_t byte;
typedef uint16_t word;

typedef struct mem {
    uint8_t data[1024 * 64];  // a generous 64 kilobytes of memory
} mem_t;

void mem_init(mem_t* mem) {
    memset(mem->data, 0x00, sizeof(mem->data));
}

void mem_write_byte(mem_t* mem, word pos, byte value) {
    mem->data[pos] = value;
}

typedef struct cpu {
    byte pc;
    byte sp;

    byte ra;
    byte rb;
    byte r1;
    byte r2;
    byte r3;
    byte r4;
    
    byte flags;

    mem_t* mem;
} cpu_t;

void cpu_reset(cpu_t* cpu, mem_t* mem) {
    cpu->flags = 0;
    cpu->pc = 0;
    cpu->sp = 0;

    cpu->ra = 0;
    cpu->rb = 0;
    cpu->r1 = 0;
    cpu->r2 = 0;
    cpu->r3 = 0;
    cpu->r4 = 0;

    cpu->mem = mem;
}

byte cpu_fetch_byte(cpu_t* cpu, int* cycles) {
    byte data = cpu->mem->data[cpu->pc];
    cpu->pc += 1;
    cycles -= 1;
    return data;
}

void cpu_print(cpu_t* cpu) {
    printf("flags: %d\n", cpu->flags);
    printf("program counter: %d\n", cpu->pc);
    printf("stack pointer: %d\n", cpu->sp);

    printf("ra: %d\n", cpu->ra);
    printf("rb: %d\n", cpu->rb);
    printf("r1: %d\n", cpu->r1);
    printf("r2: %d\n", cpu->r2);
    printf("r3: %d\n", cpu->r3);
    printf("r4: %d\n", cpu->r4);
}

void cpu_exec(cpu_t* cpu, int cycles, bool print_step) {
    while (cycles > 0) {
        byte instruction = cpu_fetch_byte(cpu, &cycles);
        if (print_step)
            cpu_print(cpu);
            printf("current byte about to run: 0x%02x\n", instruction);
        switch (instruction) {
        case 0x00:                   // NOP
            cycles -= 1;
            printf("nop\n");
            break;
        case 0x10:
            byte value = cpu_fetch_byte(cpu, &cycles);
            cpu->r1 = value;
            break;
        default:
            printf("unhandled instruction!\n");
            cycles -= 1;
            break;
        }
    }
}



int main(void) {
    cpu_t cpu;
    mem_t mem;

    mem_init(&mem);
    mem_write_byte(&mem, 0x0000, 0x10);
    mem_write_byte(&mem, 0x0001, 69);
    cpu_reset(&cpu, &mem);
    
    cpu_exec(&cpu, 5, true);

    return 0;
}