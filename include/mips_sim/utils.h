#ifndef __UTILS_H__
#define __UTILS_H__
#include <cstdint>

#define B2M(x) ((1U << x) - 1)

// pack & unpack
uint32_t unpack(uint32_t instruction, uint8_t start_bit, uint8_t bit_width);
uint32_t pack(uint32_t instruction, uint32_t value, uint8_t start_bit, uint8_t bit_width);

// sign extension
uint32_t sign_extension(uint16_t input);

// multiplier

uint32_t multiplier_2to1(bool ctrl, uint32_t in1, uint32_t in2);

#endif // __UTILS_H__