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
    virtual void reset() = 0;

    // blocks
    DataMemoryUnit data_mem;
    InstructionMemoryUnit inst_mem;
    RegisterFile reg_file;
    ALU alu;

    // internal variables
    uint32_t pc = 0; // program counter

    // helper functions
    bool is_end_of_program()
    {
        uint32_t next_inst = inst_mem.read(pc);
        return next_inst == MEMORY_DEFAULT_VALUE;
    }
};

#endif // __CPU_H__