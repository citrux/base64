#include <stdio.h>
#include "base64.h"

const char alphabet[64] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const uint8_t rev_alphabet[128] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1,
    -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
    43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1};

char error_message[100] = {};

const char* base64_error() {
  return error_message;
}

int check_error(const char *input, int i) {
  if (i == (uint8_t)-1) {
      snprintf(error_message, 100, "Invalid character at position %d: '%c'", i, input[i]);
      return 1;
  }
  return 0;
}

char get_alphabet_symbol(uint8_t index) {
  if (index > 63) {
    return -1;
  }
  return alphabet[index];
}

int8_t get_alphabet_index(char symbol) {
  if (symbol < 0) {
    return -1;
  }
  return rev_alphabet[symbol];
}

uint32_t base64_encoded_length(uint32_t data_len) {
  return (data_len + 2) / 3 * 4;
}

uint32_t base64_decoded_length(uint32_t data_len) { return data_len * 3 / 4; }

int base64_encode(const char *input, uint32_t input_length, char *output) {
  for (int read_position = 0; read_position + 2 < input_length;
       read_position += 3) {
    uint32_t buffer = 0;
    buffer |= ((uint8_t)input[read_position]) << 16;
    buffer |= ((uint8_t)input[read_position + 1]) << 8;
    buffer |= ((uint8_t)input[read_position + 2]);

    int write_position = read_position / 3 * 4;
    output[write_position++] = get_alphabet_symbol((buffer >> 18) & 0x3f);
    output[write_position++] = get_alphabet_symbol((buffer >> 12) & 0x3f);
    output[write_position++] = get_alphabet_symbol((buffer >> 6) & 0x3f);
    output[write_position++] = get_alphabet_symbol(buffer & 0x3f);
  }
  int write_position = input_length / 3 * 4;
  switch (input_length % 3) {
  case 1:
    output[write_position++] =
        get_alphabet_symbol((uint8_t)input[input_length - 1] >> 2);
    output[write_position++] =
        get_alphabet_symbol(((uint8_t)input[input_length - 1] << 4) & 0x3f);
    output[write_position++] = '=';
    output[write_position++] = '=';
    break;
  case 2:
    output[write_position++] =
        get_alphabet_symbol(((uint8_t)input[input_length - 2]) >> 2);
    output[write_position++] =
        get_alphabet_symbol((((uint8_t)input[input_length - 2]) << 4) & 0x3f |
                            (((uint8_t)input[input_length - 1]) >> 4) & 0x3f);
    output[write_position++] =
        get_alphabet_symbol((((uint8_t)input[input_length - 1]) << 2) & 0x3f);
    output[write_position++] = '=';
    break;
  default:
    break;
  }
  return write_position;
}

int base64_decode(const char *input, uint32_t input_length, char *output) {
  while (input[input_length - 1] == '=') {
    input_length -= 1;
  }
  uint8_t i;
  for (int read_position = 0; read_position + 3 < input_length;
       read_position += 4) {
    uint32_t buffer = 0;

    i = get_alphabet_index(input[read_position]);
    if (check_error(input, i)) {
      return -1;
    }
    buffer |= i << 18;

    i = get_alphabet_index(input[read_position + 1]);
    if (check_error(input, i)) {
      return -1;
    }
    buffer |= i << 12;

    i = get_alphabet_index(input[read_position + 2]);
    if (check_error(input, i)) {
      return -1;
    }
    buffer |= i << 6;

    i = get_alphabet_index(input[read_position + 3]);
    if (check_error(input, i)) {
      return -1;
    }
    buffer |= i;

    int write_position = read_position / 4 * 3;
    output[write_position++] = (uint8_t)(buffer >> 16);
    output[write_position++] = (uint8_t)(buffer >> 8);
    output[write_position++] = (uint8_t)buffer;
  }
  int write_position = input_length / 4 * 3;
  switch (input_length % 4) {
  case 0:
    break;
  case 1:
    return -1;
  case 2:
    i = get_alphabet_index(input[input_length - 2]);
    if (check_error(input, i)) {
      return -1;
    }
    output[write_position] = i << 2;

    i = get_alphabet_index(input[input_length - 1]);
    if (check_error(input, i)) {
      return -1;
    }
    output[write_position++] |= i >> 4;
    break;
  case 3:
    i = get_alphabet_index(input[input_length - 3]);
    if (check_error(input, i)) {
      return -1;
    }
    output[write_position] = i << 2;

    i = get_alphabet_index(input[input_length - 2]);
    if (check_error(input, i)) {
      return -1;
    }
    output[write_position++] |= i >> 4;

    output[write_position] = i << 4;
    i = get_alphabet_index(input[input_length - 1]);
    if (check_error(input, i)) {
      return -1;
    }
    output[write_position++] |= i >> 2;
    break;
  }
  return write_position;
}
