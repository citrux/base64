#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#include "base64.h"

int main(int argc, char *argv[]) {
  for (int i = 1000; i < 100000; i *= 10) {
    for (int j = 0; j < 10; ++j) {
      char *input = malloc(i);
      char *output = malloc(get_encoded_length(i)+1);
      char *check = malloc(i);
      FILE* fd = fopen("/dev/urandom", "rb");
      fread(input, 1, i, fd);

      double start = (double)clock() / CLOCKS_PER_SEC;
      if (encode(input, i, output)) {
        puts("encode error");
      }
      double end = (double)clock() / CLOCKS_PER_SEC;
      printf("encode: %f s, ", end - start);

      start = (double)clock() / CLOCKS_PER_SEC;
      if (decode(output, get_encoded_length(i), check)) {
        puts("decode error");
      }
      end = (double)clock() / CLOCKS_PER_SEC;
      printf("decode: %f s ", end - start);

      uint8_t fail = 0;
      for (int k = 0; k < i; ++k) {
        fail |= input[k] ^ check[k];
      }

      if (fail) {
        puts("[fail]");

      } else {
        puts("[ok]");
      }
    }
  }
  return 0;
}