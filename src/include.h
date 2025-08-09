#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ZERO_FLAG_MASK (1 << 1)
#define CARRY_FLAG_MASK (1 << 2)
#define OVERFLOW_FLAG_MASK (1 << 4)
#define SIGN_FLAG_MASK (1 << 8)

typedef uint8_t byte;
typedef uint16_t word;