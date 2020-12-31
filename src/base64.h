/*
MIT License

Copyright © 2020 Vova Abdrakhmanov (aka citrux)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Calculate length of encoded data from input length
 */
uint32_t base64_encoded_length(uint32_t data_len);

/**
 * Calculate length of decoded data from input length
 */
uint32_t base64_decoded_length(uint32_t data_len);

/**
 * Fill output with encoded input
 *
 * Output should be at least base64_encoded_length(input) bytes long
 *
 * Returns number of bytes written to output
 */
int base64_encode(const char *input, uint32_t input_length, char *output);

/**
 * Fill output with decodet input
 *
 * Output should be at least base64_decoded_length(input) bytes long
 *
 * Returns number of bytes written to output, or -1 on error.
 * For error message use base64_error()
 */
int base64_decode(const char *input, uint32_t input_length, char *output);

/**
 * Returns last error message
 */
const char* base64_error();

#ifdef __cplusplus
}
#endif
