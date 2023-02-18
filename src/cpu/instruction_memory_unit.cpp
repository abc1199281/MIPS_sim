#include "mips_sim/cpu/instruction_memory_unit.h"

//----------------------------------------------------------------------------
InstructionMemoryUnit::Instruction InstructionMemoryUnit::fetch(uint32_t address)
{
    // TODO: address protection
    L_(ldebug4) << std::hex << "address:" << address << ", read(address):" << read(address);
    return Instruction(read(address));
};

//----------------------------------------------------------------------------