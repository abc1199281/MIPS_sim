#ifndef __INSTRUCTION_MEMORY_UNIT_H__
#define __INSTRUCTION_MEMORY_UNIT_H__

#include "mips_sim/cpu/memory_unit.h"
#include "mips_sim/utils.h"
#include "mips_sim/log.h"

class InstructionMemoryUnit : public MemoryUnit
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
        uint32_t long_address;
        Instruction(uint32_t val)
            : opcode(unpack(val, 26, 6)),
              rs(unpack(val, 21, 5)),
              rt(unpack(val, 16, 5)),
              rd(unpack(val, 11, 5)),
              shamt(unpack(val, 6, 5)),
              funct(unpack(val, 0, 6)),
              address(unpack(val, 0, 16)),
              long_address(unpack(val, 0, 26))
        {
            L_(ldebug4) << std::hex << "opcode:" << int(opcode);
            L_(ldebug4) << "rs:" << int(rs);
            L_(ldebug4) << "rt:" << int(rt);
            L_(ldebug4) << "rd:" << int(rd);
            L_(ldebug4) << "shamt:" << int(shamt);
            L_(ldebug4) << "funct:" << int(funct);
            L_(ldebug4) << "address:" << int(address);
        };
    };
    InstructionMemoryUnit() = default;
    Instruction fetch(uint32_t in_address);
};

#endif /* __MEMORY_UNIT_H__ */