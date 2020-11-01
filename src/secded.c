#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BIT(x, n) ((x >> n) & 1)

uint32_t secded_encode(uint32_t x) {
    uint32_t x0 = BIT(x, 0);
    uint32_t x1 = BIT(x, 1);
    uint32_t x2 = BIT(x, 2);
    uint32_t x3 = BIT(x, 3);
    uint32_t x4 = BIT(x, 4);
    uint32_t x5 = BIT(x, 5);
    uint32_t x6 = BIT(x, 6);
    uint32_t x7 = BIT(x, 7);
    uint32_t x8 = BIT(x, 8);
    uint32_t x9 = BIT(x, 9);
    uint32_t x10 = BIT(x, 10);
    uint32_t x11 = BIT(x, 11);
    uint32_t x12 = BIT(x, 12);
    uint32_t x13 = BIT(x, 13);
    uint32_t x14 = BIT(x, 14);
    uint32_t x15 = BIT(x, 15);

    uint32_t p0 = x15 ^ x13 ^ x11 ^ x10 ^ x8 ^ x6 ^ x4 ^ x3 ^ x1 ^ x0;
    uint32_t p1 = x13 ^ x12 ^ x10 ^ x9 ^ x6 ^ x5 ^ x3 ^ x2 ^ x0;
    uint32_t p2 = x15 ^ x14 ^ x10 ^ x9 ^ x8 ^ x7 ^ x3 ^ x2 ^ x1;
    uint32_t p3 = x10 ^ x9 ^ x8 ^ x7 ^ x6 ^ x5 ^ x4;
    uint32_t p4 = x15 ^ x14 ^ x13 ^ x12 ^ x11;
    uint32_t p5 = x15 ^ x14 ^ x13 ^ x12 ^ x11 ^ x10 ^ x9 ^ x8 ^ x7 ^ x6 ^ x5
                ^ x4 ^ x3 ^ x2 ^ x1 ^ x0 ^ p0 ^ p1 ^ p2 ^ p3 ^ p4 ^ p4;

    return p0 | (p1 << 1) | (x0 << 2) | (p2 << 3) | (x1 << 4) | (x2 << 5)
        | (x3 << 6) | (p3 << 7) | (x4 << 8) | (x5 << 9) | (x6 << 10)
        | (x7 << 11) | (x8 << 12) | (x9 << 13) | (x10 << 14) | (p4 << 15)
        | (x11 << 16) | (x12 << 17) | (x13 << 18) | (x14 << 19) | (x15 << 20)
        | (p5 << 21);
}

int16_t secded_decode(int32_t c) {
    return 0;
}

int main(int argc, char* argv[]) {
    uint32_t x = atoi(argv[1]);
    uint32_t c = secded_encode(x);

    printf("encoded: %d\n", c);

    return 0;
}

