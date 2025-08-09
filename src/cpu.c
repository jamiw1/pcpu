#include "cpu.h"

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

void mov_rxi(cpu_t* cpu, int* cycles, byte* reg) {
    byte value = cpu_fetch_byte(cpu, cycles);
    *reg = value;
    *cycles -= 1;
}

void mov_rxr(cpu_t* cpu, int* cycles, byte* reg) {
    byte new_reg = cpu_fetch_byte(cpu, cycles);
    switch (new_reg) {
    case 0x00: // pc into reg
        *reg = cpu->pc;
        break;
    case 0x01: // r1 into reg
        *reg = cpu->r1;
        break;
    case 0x02: // r2 into reg
        *reg = cpu->r2;
        break;
    case 0x03: // r3 into reg
        *reg = cpu->r3;
        break;
    case 0x04: // r4 into reg
        *reg = cpu->r4;
        break;
    case 0x05: // ra into reg
        *reg = cpu->ra;
        break;
    case 0x06: // rb into reg
        *reg = cpu->rb;
        break;
    case 0x07: // sp into reg
        *reg = cpu->sp;
        break;
    default:
        printf("ultimate fail reg %d isn't valid\n", reg);
        break;
    }
    *cycles -= 1;
}

void cpu_exec(cpu_t* cpu, int cycles, bool print_step) {
    while (cycles > 0) {
        if (print_step)
            cpu_print(cpu);
        byte instruction = cpu_fetch_byte(cpu, &cycles);
        printf("current byte to run: 0x%02x\n", instruction);
        switch (instruction) {
        case 0x00:  // NOP
            cycles -= 1;
            printf("nop\n");
            break;
        case 0x10:  // MOVR1I
            mov_rxi(cpu, &cycles, &(cpu->r1));
            break;
        case 0x11: // MOVR1R
            mov_rxr(cpu, &cycles, &(cpu->r1));
            break;
        case 0x15:  // JMP
            cpu->pc = cpu->ra;
            cycles -= 1;
            break;
        case 0x1b:  // FLAG
            byte flags = cpu->flags;
            cpu->ra = flags;
            cycles -= 1;
            break;
        case 0x20:  // MOVR2I
            mov_rxi(cpu, &cycles, &(cpu->r2));
            break;
        case 0x21:  // MOVR2R
            mov_rxr(cpu, &cycles, &(cpu->r2));
            break;
        case 0x30:  // MOVR3I
            mov_rxi(cpu, &cycles, &(cpu->r3));
            break;
        case 0x31:  // MOVR3R
            mov_rxr(cpu, &cycles, &(cpu->r3));
            break;
        case 0x40:  // MOVR4I
            mov_rxi(cpu, &cycles, &(cpu->r4));
            break;
        case 0x41:  // MOVR4R
            mov_rxr(cpu, &cycles, &(cpu->r4));
            break;
        case 0x50:  // MOVRAI
            mov_rxi(cpu, &cycles, &(cpu->ra));
            break;
        case 0x51:  // MOVRAR
            mov_rxr(cpu, &cycles, &(cpu->ra));
            break;
        case 0x60:  // MOVRBI
            mov_rxi(cpu, &cycles, &(cpu->rb));
            break;
        case 0x61:  // MOVRBR
            mov_rxr(cpu, &cycles, &(cpu->rb));
            break;
        default:
            printf("unhandled instruction! treating as NOP\n");
            cycles -= 1;
            break;
        }
    }
}