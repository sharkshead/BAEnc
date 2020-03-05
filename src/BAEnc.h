/*
 * BAEnc - a simple, small footprint encrytion/decryption library.
 *
 * Copyright 2020 Graeme Elsworthy <graeme@sharkshead.com>
 */

#include <stdint.h>

// Number of times the Feistel-based round is applied to each input byte.
#define BAENC_ROUNDS         7

// Number of nibbles (4 bits) in your key. Divide this by 2 to get the number of bytes in your key.
#define BAENC_NIBBLECOUNT   32

void BAEncA(const uint8_t *src, int size, const uint8_t *key, uint8_t *dst);
void BAEncB(const uint8_t *src, int size, const uint8_t *key, uint8_t *dst);
