#ifndef __CPU_SINGLE_CYCLE_H__
#define __CPU_SINGLE_CYCLE_H__

#include <cstdint>

#include "mips_sim/cpu/cpu.h"

class CPU_SingleCycle : public CPU
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
    void process();

private:
    CtrlSignals ctrl(uint8_t opcode);
    ALU::Ctrl alu_ctrl(uint8_t funct, uint8_t ALU_Op);
};

#endif // __CPU_SINGLE_CYCLE_H__