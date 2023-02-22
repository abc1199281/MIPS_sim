#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>

#include "mips_sim/cpu/data_memory_unit.h"
#include "mips_sim/cpu/instruction_memory_unit.h"
#include "mips_sim/cpu/register_file.h"
#include "mips_sim/cpu/alu.h"

class CPU
{
public:
    struct CtrlSignals
    {
        bool Jump;
        bool RegDst;
        bool ALUSrc;
        bool MemtoReg;
        bool RegWrite;
        bool MemRead;
        bool MemWrite;
        bool Branch;
        uint8_t ALU_Op;
        CtrlSignals(uint16_t val)
            : Jump(unpack(val, 9, 1)),
              RegDst(unpack(val, 8, 1)),
              ALUSrc(unpack(val, 7, 1)),
              MemtoReg(unpack(val, 6, 1)),
              RegWrite(unpack(val, 5, 1)),
              MemRead(unpack(val, 4, 1)),
              MemWrite(unpack(val, 3, 1)),
              Branch(unpack(val, 2, 1)),
              ALU_Op(unpack(val, 0, 2)){};
    };

    // Interface
    virtual void process() = 0;
    virtual void reset() = 0;
    virtual bool is_end_of_program() = 0;

    // Blocks
    DataMemoryUnit data_mem;
    InstructionMemoryUnit inst_mem;
    RegisterFile reg_file;
    ALU alu;

    // Control Units
    CtrlSignals ctrl(uint8_t opcode);
    ALU::Ctrl alu_ctrl(uint8_t funct, uint8_t ALU_Op);

    // internal variables
    uint32_t pc = 0; // program counter
};

#endif // __CPU_H__