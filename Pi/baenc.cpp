#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "../src/BAEnc.h"


#define MSGSIZE          32
#define ITERATIONS   100000

int main(int ac, char **av) {
  uint8_t i;
  timespec startTime;
  timespec endTime;
  uint32_t count;
  uint8_t msg[MSGSIZE];
  uint8_t out[MSGSIZE];
  uint8_t out2[MSGSIZE];
  uint8_t key[BAENC_NIBBLECOUNT / 2];
  uint64_t t;
  uint64_t ts;
  uint64_t te;
  int n;
  
  srandom(getpid());
  for(i = 0; i < MSGSIZE; i++) msg[i] = random();
  for(i = 0; i < BAENC_NIBBLECOUNT / 2; i++) key[i] = random();

  printf("Rounds         %d\n", BAENC_ROUNDS);
  printf("Key length:    %d nibbles\n", BAENC_NIBBLECOUNT);
  printf("Message size:  %d bytes\n", MSGSIZE);
  printf("\n");

  printf("Input ");
  for(i = 0; i < MSGSIZE; i++) {
    printf(" %02hhx", msg[i]);
  }
  printf("\n");
  printf("Key   ");
  for(i = 0; i < BAENC_NIBBLECOUNT / 2; i++) {
    printf(" %02hhx", key[i]);
  }
  printf("\n\n");

  printf("Input -> BAEncA -> BAEncB\n");
  printf("Input ");
  for(i = 0; i < MSGSIZE; i++) {
    printf(" %02hx", msg[i]);
  }
  printf("\n");
  BAEncA(msg, MSGSIZE, key, out);
  printf("BAEncA");
  for(count = 0; count < MSGSIZE; count++) {
    printf(" %02hx", out[count]);
  }
  printf("\n");
  BAEncB(out, MSGSIZE, key, out2);
  printf("BAEncB");
  for(count = 0; count < MSGSIZE; count++) {
    printf(" %02hx", out2[count]);
  }
  printf("\n\n");

  printf("Input -> BAEncB -> BAEncA\n");
  printf("Input ");
  for(i = 0; i < MSGSIZE; i++) {
    printf(" %02hx", msg[i]);
  }
  printf("\n");
  BAEncB(msg, MSGSIZE, key, out);
  printf("BAEncB");
  for(count = 0; count < MSGSIZE; count++) {
    printf(" %02hx", out[count]);
  }
  printf("\n");
  BAEncA(out, MSGSIZE, key, out2);
  printf("BAEncA");
  for(count = 0; count < MSGSIZE; count++) {
    printf(" %02hx", out2[count]);
  }
  printf("\n\n");

  printf("Timing tests\n");
  printf("Iterations:    %d\n", ITERATIONS);
  printf("\n");
  
  printf("BAEncA ");
  clock_gettime(CLOCK_REALTIME, &startTime);
  for(count = 0; count < ITERATIONS; count++) {
    BAEncA(msg, MSGSIZE, key, out);
  }
  clock_gettime(CLOCK_REALTIME, &endTime);
  ts = startTime.tv_sec;
  ts *= 1000000000;
  ts += startTime.tv_nsec;
  te = endTime.tv_sec;
  te *= 1000000000;
  te += endTime.tv_nsec;
  t = te - ts;
  t = t / ITERATIONS;       // ns per message
  t = t / MSGSIZE;          // ns per byte
  printf("%lld ns per byte\n", t);

  printf("BAEncB ");
  clock_gettime(CLOCK_REALTIME, &startTime);
  for(count = 0; count < ITERATIONS; count++) {
    BAEncB(msg, MSGSIZE, key, out);
  }
  clock_gettime(CLOCK_REALTIME, &endTime);
  ts = startTime.tv_sec;
  ts *= 1000000000;
  ts += startTime.tv_nsec;
  te = endTime.tv_sec;
  te *= 1000000000;
  te += endTime.tv_nsec;
  t = te - ts;
  t = t / ITERATIONS;       // ns per message
  t = t / MSGSIZE;          // ns per byte
  printf("%lld ns per byte\n", t);

  return 0;
}
