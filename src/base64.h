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

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * If output is NULL, just returns expected length of output buffer 
 * Otherwise, fill output with encoded data
 *
 */
size_t base64_encode(const char *input, size_t input_length, char *output);

/**
 *
 * If output is NULL, just returns expected length of output buffer 
 * Otherwise, fill output with decoded data
 *
 */
size_t base64_decode(const char *input, size_t input_length, char *output);

/**
 *
 * Check input before decoding
 * Returns position of error character or input_length if no error found
 *
 */
size_t base64_check(const char *input, size_t input_length);


#ifdef __cplusplus
}
#endif
