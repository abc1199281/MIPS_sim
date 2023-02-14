#ifndef __INSTRUCTION_MEMORY_UNIT_H__
#define __INSTRUCTION_MEMORY_UNIT_H__

#include "mips_sim/cpu/memory_unit.h"

class InstructionMemoryUnit : private MemoryUnit
{
public:
    InstructionMemoryUnit() = default;
    void process(uint32_t in_address, uint32_t &out_value);
};

#endif /* __MEMORY_UNIT_H__ */