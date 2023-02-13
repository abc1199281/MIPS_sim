#ifndef __UTILS_H__
#define __UTILS_H__
#include <cstdint>

#define B2M(x) ((1 << x) - 1)

uint32_t unpack(uint32_t instruction, uint8_t start_bit, uint8_t bit_width);
uint32_t pack(uint32_t instruction, uint32_t value, uint8_t start_bit, uint8_t bit_width);

#endif // __UTILS_H__