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

uint32_t get_encoded_length(uint32_t data_len) {
  return (data_len + 2) / 3 * 4;
}

uint32_t get_decoded_length(uint32_t data_len) { return data_len * 3 / 4; }

int encode(const char *input, uint32_t input_length, char *output) {
  uint8_t bits_in_buffer = 0;
  uint16_t buffer = 0;
  uint32_t read_position = 0;
  uint32_t write_position = 0;
  while (read_position < input_length || bits_in_buffer >= 6) {
    if (bits_in_buffer < 6) {
      uint16_t chunk = (uint8_t)input[read_position++];
      buffer |= chunk << (8 - bits_in_buffer);
      bits_in_buffer += 8;
    }
    char c = get_alphabet_symbol(buffer >> 10);
    if (c == -1) {
      return -1;
    }
    output[write_position++] = c;
    buffer <<= 6;
    bits_in_buffer -= 6;
  }
  if (bits_in_buffer) {
    char c = get_alphabet_symbol(buffer >> 10);
    if (c == -1) {
      return -1;
    }
    switch (bits_in_buffer) {
    case 2:
      output[write_position++] = c;
      output[write_position++] = '=';
      output[write_position++] = '=';
      break;
    case 4:
      output[write_position++] = c;
      output[write_position++] = '=';
      break;
    default:
      break;
    }
  }
  return write_position;
}

int decode(const char *input, uint32_t input_length, char *output) {
  uint8_t bits_in_buffer = 0;
  uint16_t buffer = 0;
  uint32_t read_position = 0;
  uint32_t write_position = 0;
  while (read_position < input_length) {
    if (bits_in_buffer < 8) {
      char c = input[read_position++];
      if (c == '=') {
        bits_in_buffer = 0;
        break;
      }
      uint8_t i = get_alphabet_index(c);
      if (i == (uint8_t)-1) {
        return -1;
      }
      uint16_t chunk = i;
      buffer |= chunk << (10 - bits_in_buffer);
      bits_in_buffer += 6;
    } else {
      output[write_position++] = buffer >> 8;
      buffer <<= 8;
      bits_in_buffer -= 8;
    }
  }
  if (bits_in_buffer) {
    output[write_position++] = buffer >> 8;
  }
  return write_position;
}
