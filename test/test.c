#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "../src/secded.h"

#define LOOP_SIZE 100000
#define RANDOM_WORD (rand() % (INT16_MAX - INT16_MIN + 1) + INT16_MIN)

void test_no_errors() {
    int fails = 0;
    for (int i = 0; i < LOOP_SIZE; i++) {
        int16_t d = RANDOM_WORD;
        int32_t c = secded_encode(d);
        int32_t c_decoded;
        int status = secded_decode(c, &c_decoded);
        fails = (c == c_decoded && status == STATUS_NO_ERR)
            ? fails
            : fails + 1;
    }

    if (fails == 0) {
        printf("No bit errors: all passed\n");
    } else {
        printf("No bit errors: %d failed\n", fails);
    }
}

void test_parity_error() {
    int fails = 0;
    for (int i = 0; i < LOOP_SIZE; i++) {
        int16_t d = RANDOM_WORD;
        int32_t c = secded_encode(d);
        int32_t c_altered = c;
        c_altered ^= (1 << 21);
        int32_t c_decoded;
        int status = secded_decode(c_altered, &c_decoded);
        fails = (c_decoded == c && status == STATUS_PARITY_ERR)
            ? fails
            : fails + 1;
    }

    if (fails == 0) {
        printf("Parity error: all passed\n");
    } else {
        printf("Parity error: %d failed\n", fails);
    }
}

void test_single_error() {
    int fails = 0;
    for (int i = 0; i < LOOP_SIZE; i++) {
        int16_t d = RANDOM_WORD;
        int32_t c = secded_encode(d);
        int pos = rand() % 21;
        int32_t c_altered = c;
        c_altered ^= (1 << pos);
        int32_t c_decoded;
        int status = secded_decode(c_altered, &c_decoded);
        fails = (c_decoded == c && status == STATUS_SINGLE_ERR)
            ? fails
            : fails + 1;
    }

    if (fails == 0) {
        printf("Single error: all passed\n");
    } else {
        printf("Single error: %d failed\n", fails);
    }
}

void test_double_error() {
    int fails = 0;
    for (int i = 0; i < LOOP_SIZE; i++) {
        int16_t d = RANDOM_WORD;
        int32_t c = secded_encode(d);

        int pos1 = rand() % 21;
        int pos2;
        while ((pos2 = rand() % 21) == pos1);
        int32_t c_altered = c;
        c_altered ^= (1 << pos1);
        c_altered ^= (1 << pos2);

        int32_t c_decoded;
        int status = secded_decode(c_altered, &c_decoded);
        fails = c_decoded != c && status == STATUS_DOUBLE_ERR
            ? fails
            : fails + 1;
    }

    if (fails == 0) {
        printf("Double error: all passed\n");
    } else {
        printf("Double error: %d failed\n", fails);
    }
}

int main() {
    test_no_errors();
    test_parity_error();
    test_single_error();
    test_double_error();
}

