#include "include.h"
#include "mem.h"

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

void cpu_reset(cpu_t* cpu, mem_t* mem);
byte cpu_fetch_byte(cpu_t* cpu, int* cycles);
void cpu_print(cpu_t* cpu);
void cpu_exec(cpu_t* cpu, int cycles, bool print_step);