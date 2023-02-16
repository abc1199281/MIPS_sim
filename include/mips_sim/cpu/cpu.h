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
    virtual void process() = 0;

    // blocks
    DataMemoryUnit data_mem;
    InstructionMemoryUnit inst_mem;
    RegisterFile reg_file;
    ALU alu;

    // internal variables
    uint32_t pc; // program counter
    uint32_t cpu_out = 0;
};

#endif // __CPU_H__