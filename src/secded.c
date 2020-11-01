#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BIT(x, n) ((x >> n) & 1)

uint32_t secded_encode(uint16_t x) {
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
                ^ x4 ^ x3 ^ x2 ^ x1 ^ x0 ^ p0 ^ p1 ^ p2 ^ p3 ^ p4;

    return p0 | (p1 << 1) | (x0 << 2) | (p2 << 3) | (x1 << 4) | (x2 << 5)
        | (x3 << 6) | (p3 << 7) | (x4 << 8) | (x5 << 9) | (x6 << 10)
        | (x7 << 11) | (x8 << 12) | (x9 << 13) | (x10 << 14) | (p4 << 15)
        | (x11 << 16) | (x12 << 17) | (x13 << 18) | (x14 << 19) | (x15 << 20)
        | (p5 << 21);
}

int secded_decode(uint32_t c, uint16_t* x) {
    uint32_t x0 = BIT(c, 2);
    uint32_t x1 = BIT(c, 4);
    uint32_t x2 = BIT(c, 5);
    uint32_t x3 = BIT(c, 6);
    uint32_t x4 = BIT(c, 8);
    uint32_t x5 = BIT(c, 9);
    uint32_t x6 = BIT(c, 10);
    uint32_t x7 = BIT(c, 11);
    uint32_t x8 = BIT(c, 12);
    uint32_t x9 = BIT(c, 13);
    uint32_t x10 = BIT(c, 14);
    uint32_t x11 = BIT(c, 16);
    uint32_t x12 = BIT(c, 17);
    uint32_t x13 = BIT(c, 18);
    uint32_t x14 = BIT(c, 19);
    uint32_t x15 = BIT(c, 20);

    uint32_t p0_read = BIT(c, 0);
    uint32_t p1_read = BIT(c, 1);
    uint32_t p2_read = BIT(c, 3);
    uint32_t p3_read = BIT(c, 7);
    uint32_t p4_read = BIT(c, 15);
    uint32_t p5_read = BIT(c, 21);

    uint32_t p0_calc = x15 ^ x13 ^ x11 ^ x10 ^ x8 ^ x6 ^ x4 ^ x3 ^ x1 ^ x0;
    uint32_t p1_calc = x13 ^ x12 ^ x10 ^ x9 ^ x6 ^ x5 ^ x3 ^ x2 ^ x0;
    uint32_t p2_calc = x15 ^ x14 ^ x10 ^ x9 ^ x8 ^ x7 ^ x3 ^ x2 ^ x1;
    uint32_t p3_calc = x10 ^ x9 ^ x8 ^ x7 ^ x6 ^ x5 ^ x4;
    uint32_t p4_calc = x15 ^ x14 ^ x13 ^ x12 ^ x11;
    uint32_t p5_calc = x15 ^ x14 ^ x13 ^ x12 ^ x11 ^ x10 ^ x9 ^ x8 ^ x7 ^ x6 ^ x5
                ^ x4 ^ x3 ^ x2 ^ x1 ^ x0 ^ p0_read ^ p1_read ^ p2_read
                ^ p3_read ^ p4_read;

    uint8_t syndrome = (p0_read ^ p0_calc) << 0
                     | (p1_read ^ p1_calc) << 1
                     | (p2_read ^ p2_calc) << 2
                     | (p3_read ^ p3_calc) << 3
                     | (p4_read ^ p4_calc) << 4;

    int status;

    if (syndrome == 0) {
        if (p5_read == p5_calc) {
            // no errors
            status = 0;
        } else {
            // single correctable error in parity bit, so we flip that bit
            c ^= 1 << 21;
            status = 1;      
        }
    } else {
        if (p5_read == p5_calc) {
            // incorrectable double error
            status = -1;
        } else {
            // single correctable error, flip bit at pos indicated by syndrome
            c ^= 1 << (syndrome - 1);
            status = 2;
        }
    }

    *x = BIT(c, 2) | (BIT(c, 4) << 1) | (BIT(c, 5) << 2) | (BIT(c, 6) << 3) | (BIT(c, 8) << 4) | (BIT(c, 9) << 5)
        | (BIT(c, 10) << 6) | (BIT(c, 11) << 7) | (BIT(c, 12) << 8) | (BIT(c, 13) << 9) | (BIT(c, 14) << 10)
        | (BIT(c, 16) << 11) | (BIT(c, 17) << 12) | (BIT(c, 18) << 13) | (BIT(19, 14) << 14) | (BIT(c, 20) << 15);

    return status;
}

int main(int argc, char* argv[]) {
    uint16_t x = atoi(argv[1]);
    uint32_t c = secded_encode(x);

    // artificially flip one bit
    c ^= (1 << 17);
    
    uint16_t d;
    int status = secded_decode(c, &d);

    printf("status: %d\n", status);
    printf("decoded: %d\n", d);

    return 0;
}

