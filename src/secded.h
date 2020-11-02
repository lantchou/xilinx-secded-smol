#ifndef SECDED_H
#define SECDED_H

#include <stdint.h>

/**
 * Encodes a 16-bit data word into a 22-bit code word using the Xilinx
 * Coolrunner II SEC-DED code.
 *
 * @param d The 16-bit data word to be encoded
 * @return 32-bit integer holding the encoded 22 bit word
 * */
int32_t secded_encode(int16_t d);

/**
 * Decodes a 22-bit SEC-DED code word. Depending on the amount of bit errors
 * that occured inside the code word, errors can be detected or even corrected.
 *
 * @param c The 22-bit code word to be decoded
 * @param x Pointer to integer where decoded data word should be stored
 * @return Integer indicating status of decoding. This status says whether any
 *         bit errors occured, and if so, how many occured and whether they
 *         have been corrected. The possible status codes are
 *           -1: incorrectable double bit error
 *            0: no errors
 *            1: corrected single bit error in parity bit (bit at position 21)
 *            2: corrected single bit error elsewhere
 * */
int secded_decode(int32_t c, int16_t* x);

#endif

