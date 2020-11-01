#include <stdio.h>
#include <stdlib.h>

#define BIT(x, n) ((x >> n) & 1)

int32_t secded_encode(int16_t x) {
    int8_t x0 = BIT(x, 0);
    int8_t x1 = BIT(x, 1);
    int8_t x2 = BIT(x, 2);
    int8_t x3 = BIT(x, 3);
    int8_t x4 = BIT(x, 4);
    int8_t x5 = BIT(x, 5);
    int8_t x6 = BIT(x, 6);
    int8_t x7 = BIT(x, 7);
    int8_t x8 = BIT(x, 8);
    int8_t x9 = BIT(x, 9);
    int8_t x10 = BIT(x, 10);
    int8_t x11 = BIT(x, 11);
    int8_t x12 = BIT(x, 12);
    int8_t x13 = BIT(x, 13);
    int8_t x14 = BIT(x, 14);
    int8_t x15 = BIT(x, 15);

    int8_t p0 = x15 ^ x13 ^ x11 ^ x10 ^ x8 ^ x6 ^ x4 ^ x3 ^ x1 ^ x0;
    int8_t p1 = x13 ^ x12 ^ x10 ^ x9 ^ x6 ^ x5 ^ x3 ^ x2 ^ x0;
    int8_t p2 = x15 ^ x14 ^ x10 ^ x9 ^ x8 ^ x7 ^ x3 ^ x2 ^ x1;
    int8_t p3 = x10 ^ x9 ^ x8 ^ x7 ^ x6 ^ x5 ^ x4;
    int8_t p4 = x15 ^ x14 ^ x13 ^ x12 ^ x11;
    int8_t p5 = x15 ^ x14 ^ x13 ^ x12 ^ x11 ^ x10 ^ x9 ^ x8 ^ x7 ^ x6 ^ x5
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
    int16_t x = atoi(argv[1]);
    int32_t c = secded_encode(x);

    printf("decoded: %d\n", c);

    return 0;
}

