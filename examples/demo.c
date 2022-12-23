#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "base64.h"

int main(int argc, char *argv[]) {
  // Encoding
  char *input = "Text to be encoded";

  // 1. Get length of output buffer
  int enc_len = base64_encode(input, strlen(input), NULL);

  // 2. Allocate output buffer (+1 for '\0' at the end)
  char *encoded = calloc(enc_len + 1, sizeof(char));

  // 3. Encode
  base64_encode(input, strlen(input), encoded);


  // Decoding
  // 1. Check input
  size_t error_pos = base64_check(encoded, strlen(encoded));
  if (error_pos != strlen(encoded)) {
    puts("Decoding failed!");
    printf("Invalid character in position %ld: %c\n", error_pos, encoded[error_pos]);
    exit(1);
  }
  // 2. Get length of output buffer
  int dec_len = base64_decode(encoded, strlen(encoded), NULL);
  
  // 3. Allocate output buffer (+1 for '\0' at the end)
  char *decoded = calloc(dec_len + 1, sizeof(char));

  // 4. Decode
  dec_len = base64_decode(encoded, strlen(encoded), decoded);

  assert(strcmp(input, decoded) == 0);

  return 0;
}
