#include "BAEnc.h"

__attribute__ ((noinline)) void BAEncA(const uint8_t *src, int size, const uint8_t *key, uint8_t *dst) {
  uint8_t i;
  uint8_t s;
  uint8_t n;
  uint8_t k;
  uint8_t nibble;
  uint8_t c;

  n = 0;
  k = key[0];
  for(i = 0; i < size; i++) {
    c = *src++;
    for(s = 0; s < BAENC_ROUNDS; s++) {
      if((n & 0x01) == 0) nibble = k >> 4;
      else nibble = k & 0x0f;
      c = (c << 4) | (nibble ^ (((c & 0x0f) + n) & 0x0f) ^ (c >> 4));
      n++;
      if(n >= BAENC_NIBBLECOUNT) n = 0;
      k = key[n / 2];
    }
    *dst++ = (c << 4) | (c >> 4);
  }
}

__attribute__ ((noinline)) void BAEncB(const uint8_t *src, int size, const uint8_t *key, uint8_t *dst) {
  int i;
  int s;
  int n;
  uint8_t k;
  uint8_t nibble;
  uint8_t c;

  n = BAENC_ROUNDS - 1;
  while(n >= BAENC_NIBBLECOUNT) n -= BAENC_NIBBLECOUNT;
  k = key[n / 2];
  for(i = 0; i < size; i++) {
    c = *src++;
    for(s = 0; s < BAENC_ROUNDS; s++) {
      if((n & 0x01) == 0) nibble = k >> 4;
      else nibble = k & 0x0f;
      c = (c << 4) | (nibble ^ (((c & 0x0f) + n) & 0x0f) ^ (c >> 4));
      n--;
      if(n < 0) n = BAENC_NIBBLECOUNT - 1;
      k = key[n / 2];
    }
    *dst++ = (c << 4) | (c >> 4);
    n += 2 * BAENC_ROUNDS;
    while(n >= BAENC_NIBBLECOUNT) n -= BAENC_NIBBLECOUNT;
    k = key[n / 2];
  }
}
