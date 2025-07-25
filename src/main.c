#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
} cpu_t;

void cpu_init(cpu_t* cpu) {
    cpu->flags = 0;
    cpu->pc = 0;
    cpu->sp = 0;

    cpu->ra = 0;
    cpu->rb = 0;
    cpu->r1 = 0;
    cpu->r2 = 0;
    cpu->r3 = 0;
    cpu->r4 = 0;
}

int main(void) {
    printf("Hello, world!\n");
    return 0;
}