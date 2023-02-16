#ifndef __INSTRUCTION_MEMORY_UNIT_H__
#define __INSTRUCTION_MEMORY_UNIT_H__

#include "mips_sim/cpu/memory_unit.h"
#include "mips_sim/utils.h"

class InstructionMemoryUnit : private MemoryUnit
{
public:
    struct Instruction
    {
        uint8_t opcode;
        uint8_t rs;
        uint8_t rt;
        uint8_t rd;
        uint8_t shamt;
        uint8_t funct;
        uint16_t address;
        Instruction(uint32_t val)
            : opcode(unpack(val, 26, 6)),
              rs(unpack(val, 21, 5)),
              rt(unpack(val, 16, 5)),
              rd(unpack(val, 11, 5)),
              shamt(unpack(val, 6, 5)),
              funct(unpack(val, 0, 5)),
              address(unpack(val, 0, 16)){};
    };
    InstructionMemoryUnit() = default;
    Instruction fetch(uint32_t in_address);
};

#endif /* __MEMORY_UNIT_H__ */