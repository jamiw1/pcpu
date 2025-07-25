#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;

struct cpu {
    byte pc;
    byte sp;

    byte ra;
    byte rb;
    byte r1;
    byte r2;
    byte r3;
    byte r4;

    
};

int main(void)
{
    printf("Hello, world!\n");
    return 0;
}