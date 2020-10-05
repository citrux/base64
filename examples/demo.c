#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char* input = argv[1];

    int out_len = get_encoded_length(strlen(input));
    char *output = calloc(out_len+1, sizeof(char));
    memset(output, 0, out_len+1);

    encode(input, strlen(input), output);
    puts(output);

    int out1_len = get_decoded_length(strlen(input));
    char *output1 = calloc(out1_len+1, sizeof(char));
    memset(output1, 0, out1_len+1);

    decode(output, strlen(output), output1);
    puts(output1);
    return 0;
}
