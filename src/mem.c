#include "mem.h"

typedef struct mem {
    uint8_t data[1024 * 64];  // a generous 64 kilobytes of memory
} mem_t;

void mem_init(mem_t* mem) {
    memset(mem->data, 0x00, sizeof(mem->data));
}

void mem_write_byte(mem_t* mem, word pos, byte value) {
    mem->data[pos] = value;
}