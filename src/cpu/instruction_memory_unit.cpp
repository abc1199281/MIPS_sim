#include "mips_sim/cpu/instruction_memory_unit.h"

//----------------------------------------------------------------------------
void InstructionMemoryUnit::process(uint32_t in_address, uint32_t &out_value)
{
    out_value = read(in_address);
};

//----------------------------------------------------------------------------