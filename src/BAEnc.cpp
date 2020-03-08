/*

MIT License

Copyright (c) 2020 Graeme Elsworthy <github@sharkshead.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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
      c = (c << 4) | (nibble ^ ((c + n) & 0x0f) ^ (c >> 4));
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
      c = (c << 4) | (nibble ^ ((c + n) & 0x0f) ^ (c >> 4));
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
