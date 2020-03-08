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

//
// Sketch that shows the encryption and decryption of a random message, using a random key,
// in both A -> B and B -> A directions.
//

#include <BAEnc.h>

#define MSGSIZE          32
#define ITERATIONS    10000

void setup() {
  uint8_t i;
  uint32_t startTime;
  uint32_t endTime;
  uint32_t count;
  uint8_t msg[MSGSIZE];
  uint8_t out[MSGSIZE];
  uint8_t out2[MSGSIZE];
  uint8_t key[BAENC_NIBBLECOUNT / 2];
  uint64_t t;
  int n;
  char buf[32];
  
  Serial.begin(57600);

  randomSeed(analogRead(A0) + analogRead(A1) + analogRead(A3));
  for(i = 0; i < MSGSIZE; i++) msg[i] = random(0, 255);
  for(i = 0; i < BAENC_NIBBLECOUNT / 2; i++) key[i] = random(0, 255);

  Serial.print("Rounds         "); Serial.println(BAENC_ROUNDS);
  Serial.print("Key length:    "); Serial.print(BAENC_NIBBLECOUNT); Serial.println(" nibbles");
  Serial.print("Message size:  "); Serial.print(MSGSIZE); Serial.println(" bytes");
  Serial.println();

  Serial.print("Input ");
  for(i = 0; i < MSGSIZE; i++) {
    sprintf(buf, " %02hx", msg[i]);
    Serial.print(buf);
  }
  Serial.println();
  Serial.print("Key   ");
  for(i = 0; i < BAENC_NIBBLECOUNT / 2; i++) {
    sprintf(buf, " %02hx", key[i]);
    Serial.print(buf);
  }
  Serial.println();
  Serial.println();

  Serial.println("Input -> BAEncA -> BAEncB");
  Serial.print("Input ");
  for(i = 0; i < MSGSIZE; i++) {
    sprintf(buf, " %02hx", msg[i]);
    Serial.print(buf);
  }
  Serial.println();
  BAEncA(msg, MSGSIZE, key, out);
  Serial.print("BAEncA");
  for(count = 0; count < MSGSIZE; count++) {
    sprintf(buf, " %02hx", out[count]);
    Serial.print(buf);
  }
  Serial.println();
  BAEncB(out, MSGSIZE, key, out2);
  Serial.print("BAEncB");
  for(count = 0; count < MSGSIZE; count++) {
    sprintf(buf, " %02hx", out2[count]);
    Serial.print(buf);
  }
  Serial.println();
  Serial.println();

  Serial.println("Input -> BAEncB -> BAEncA");
  Serial.print("Input ");
  for(i = 0; i < MSGSIZE; i++) {
    sprintf(buf, " %02hx", msg[i]);
    Serial.print(buf);
  }
  Serial.println();
  BAEncB(msg, MSGSIZE, key, out);
  Serial.print("BAEncB");
  for(count = 0; count < MSGSIZE; count++) {
    sprintf(buf, " %02hx", out[count]);
    Serial.print(buf);
  }
  Serial.println();
  BAEncA(out, MSGSIZE, key, out2);
  Serial.print("BAEncA");
  for(count = 0; count < MSGSIZE; count++) {
    sprintf(buf, " %02hx", out2[count]);
    Serial.print(buf);
  }
  Serial.println();
  Serial.println();

  Serial.println("Timing tests");
  Serial.print("Iterations:    "); Serial.println(ITERATIONS);
  Serial.println();
  
  Serial.print("BAEncA ");
  startTime = millis();
  for(count = 0; count < ITERATIONS; count++) {
    BAEncA(msg, MSGSIZE, key, out);
  }
  endTime = millis();
  t = endTime - startTime;  // ms
  t = t * 1000000;          // ns
  t = t / ITERATIONS;       // ns per message
  t = t / MSGSIZE;          // ns per byte
  Serial.print((uint32_t) t);
  Serial.println(" ns per byte");

  Serial.print("BAEncB ");
  startTime = millis();
  for(count = 0; count < ITERATIONS; count++) {
    BAEncB(msg, MSGSIZE, key, out);
  }
  endTime = millis();
  t = endTime - startTime;  // ms
  t = t * 1000000;          // ns
  t = t / ITERATIONS;       // ns per message
  t = t / MSGSIZE;          // ns per byte
  Serial.print((uint32_t) t);
  Serial.println(" ns per byte");
  Serial.println();
}

void loop() {
}
