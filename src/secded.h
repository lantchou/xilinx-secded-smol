#ifndef SECDED_H
#define SECDED_H

#include <stdint.h>

#define STATUS_NO_ERR 0
#define STATUS_SINGLE_ERR 1
#define STATUS_DOUBLE_ERR 2
#define STATUS_PARITY_ERR 3

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
 * @param c_decoded Pointer to integer where decoded code word must be stored
 * @return Integer indicating status of decoding. This status says whether any
 *         bit errors occured, and if so, how many occured and whether they
 *         have been corrected. The possible status codes are
 *           0: no errors
 *           1: corrected single bit error in parity bit (bit at position 21)
 *           2: incorrectable double bit error
 *           3: corrected single bit error (not in parity bit)
 * */
int secded_decode(int32_t c, int32_t* c_decoded);

#endif

