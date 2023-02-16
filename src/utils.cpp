#include "mips_sim/utils.h"

//-------------------------------------------------------------------------------------------------
uint32_t unpack(uint32_t instruction, uint8_t start_bit, uint8_t bit_width)
{
    return (instruction >> start_bit) & B2M(bit_width);
}

//-------------------------------------------------------------------------------------------------
uint32_t pack(uint32_t instruction, uint32_t value, uint8_t start_bit, uint8_t bit_width)
{
    uint32_t mask = B2M(bit_width) << start_bit;
    return (value << start_bit & mask) | (instruction & ~mask);
}

//-------------------------------------------------------------------------------------------------

uint32_t sign_extension(uint16_t input)
{
    // Note: only 16 bits to 32 bits.
    static const uint32_t mask = 1U << (16 - 1);
    input = input & B2M(16);
    return (input ^ mask) - mask;
}
//-------------------------------------------------------------------------------------------------

uint32_t multiplier_2to1(bool ctrl, uint32_t in1, uint32_t in2)
{
    return ctrl ? in1 : in2;
}
//-------------------------------------------------------------------------------------------------