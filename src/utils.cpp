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