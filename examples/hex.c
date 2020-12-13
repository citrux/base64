#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <hex string>\n", argv[0]);
    return 1;
  }

  char *hex_input = argv[1];
  int hexlen = strlen(hex_input);
  if (hexlen % 2) {
    puts("Hex string should have even length");
    return 1;
  }

  char *input = calloc(hexlen / 2, sizeof(char));
  for (int i = 0; i < hexlen / 2; ++i) {
    char x[] = {hex_input[2 * i], hex_input[2 * i + 1], '\0'};
    input[i] = strtol(x, NULL, 16);
  }

  int out_len = base64_encoded_length(strlen(input));
  printf("input length: %lu, encoded length: %d\n", strlen(input), out_len);
  char *output = calloc(out_len + 1, sizeof(char));
  memset(output, 0, out_len + 1);

  if (base64_encode(input, strlen(input), output) == -1) {
    puts("Encoding failed!");
    exit(1);
  }
  puts(output);
  int out1_len = base64_decoded_length(out_len);
  char *output1 = calloc(out1_len + 1, sizeof(char));
  memset(output1, 0, out1_len + 1);

  out1_len = base64_decode(output, strlen(output), output1);
  if (out1_len == -1) {
    puts("Decoding failed!");
    puts(base64_error());
    exit(1);
  }
  printf("decoded length: %d\n", out1_len);

  for (int i = 0; i < out1_len; ++i) {
    printf("%02x", (uint8_t)output1[i]);
  }
  puts("");
  return 0;
}
