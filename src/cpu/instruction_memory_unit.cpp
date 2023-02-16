#include "mips_sim/cpu/instruction_memory_unit.h"

//----------------------------------------------------------------------------
InstructionMemoryUnit::Instruction InstructionMemoryUnit::fetch(uint32_t address)
{
    // TODO: address protection
    return Instruction(read(address));
};

//----------------------------------------------------------------------------