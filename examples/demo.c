#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "base64.h"

int main(int argc, char *argv[]) {
  // Encoding
  char *input = "Text to be encoded";

  // 1. Get length of output buffer
  int enc_len = base64_encoded_length(strlen(input));

  // 2. Allocate output buffer (+1 for '\0' at the end)
  char *encoded = calloc(enc_len + 1, sizeof(char));
  memset(encoded, 0, enc_len + 1);

  // 3. Encode
  base64_encode(input, strlen(input), encoded);


  // Decoding
  // 1. Get length of output buffer
  int dec_len = base64_decoded_length(strlen(encoded));
  
  // 2. Allocate output buffer (+1 for '\0' at the end)
  char *decoded = calloc(dec_len + 1, sizeof(char));
  memset(decoded, 0, dec_len + 1);

  // 3. Decode
  dec_len = base64_decode(encoded, strlen(encoded), decoded);
  
  // 4. Check decode errors
  if (dec_len == -1) {
    puts("Decoding failed!");
    puts(base64_error());
    exit(1);
  }

  assert(strcmp(input, decoded) == 0);

  return 0;
}
