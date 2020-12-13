#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t base64_encoded_length(uint32_t data_len);
uint32_t base64_decoded_length(uint32_t data_len);
int base64_encode(const char *input, uint32_t input_length, char *output);
int base64_decode(const char *input, uint32_t input_length, char *output);
const char* base64_error();

#ifdef __cplusplus
}
#endif
