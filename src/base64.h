#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t get_encoded_length(uint32_t data_len);
uint32_t get_decoded_length(uint32_t data_len);
int encode(const char *input, uint32_t input_length, char *output);
int decode(const char *input, uint32_t input_length, char *output);
const char* base64_strerror();

#ifdef __cplusplus
}
#endif
