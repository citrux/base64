#pragma once

#include <stdint.h>

uint32_t get_encoded_length(uint32_t data_len);
uint32_t get_decoded_length(uint32_t data_len);
int encode(const char *input, uint32_t input_length, char *output);
int decode(const char *input, uint32_t input_length, char *output);
