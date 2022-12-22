#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "base64.h"

int main(int argc, char *argv[]) {
  for (size_t input_length = 131072; input_length < 10000000; input_length *= 2) {
    size_t output_length = base64_encode(NULL, input_length, NULL);

    char *input = malloc(input_length);
    char *output = malloc(output_length);
    char *check = malloc(input_length);

    double encode_min = DBL_MAX;
    double encode_max = 0;
    double encode_avg = 0;
    double encode_geo = 1;

    double decode_min = DBL_MAX;
    double decode_max = 0;
    double decode_avg = 0;
    double decode_geo = 1;

    int repetitions = 10;
    int failed = 0;

    for (int j = 0; j < repetitions; ++j) {
      FILE *fd = fopen("/dev/urandom", "rb");
      fread(input, 1, input_length, fd);

      double start = (double)clock() / CLOCKS_PER_SEC;
      if (base64_encode(input, input_length, output) == -1) {
        puts("encode error");
      }
      double end = (double)clock() / CLOCKS_PER_SEC;
      double dt = (end - start) * 1000;
      if (dt < encode_min) {
        encode_min = dt;
      }
      if (dt > encode_max) {
        encode_max = dt;
      }
      encode_avg += (dt - encode_avg) / (j + 1);
      encode_geo *= pow(dt / encode_geo, 1.0 / (j + 1));
      int right_pad = 0;
      while (output[output_length - 1 - right_pad] == '=') {
        right_pad += 1;
      }
      start = (double)clock() / CLOCKS_PER_SEC;
      if (base64_decode(output, output_length, check) == -1) {
        puts("decode error:");
        puts(base64_error());
      }
      end = (double)clock() / CLOCKS_PER_SEC;

      dt = (end - start) * 1000;
      if (dt < decode_min) {
        decode_min = dt;
      }
      if (dt > decode_max) {
        decode_max = dt;
      }
      decode_avg += (dt - decode_avg) / (j + 1);
      decode_geo *= pow(dt / decode_geo, 1.0 / (j + 1));

      uint8_t fail = 0;
      for (int k = 0; k < input_length; ++k) {
        if (input[k] ^ check[k]) {
          printf("mismatch at position %d: got \\x%02x, expected \\x%02x\n", k,
                 (uint8_t)check[k], (uint8_t)input[k]);
          break;
        }
      }

      if (fail) {
        failed += 1;
      }
    }
    free(input);
    free(output);
    free(check);
    printf("input length = %d: %d success, %d failed\n", input_length,
           repetitions - failed, failed);
    printf("encode: min/geo/avg/max = %.3f/%.3f/%.3f/%.3f ms\n", encode_min,
           encode_geo, encode_avg, encode_max);
    printf("decode: min/geo/avg/max = %.3f/%.3f/%.3f/%.3f ms\n", decode_min,
           decode_geo, decode_avg, decode_max);
  }
  return 0;
}
