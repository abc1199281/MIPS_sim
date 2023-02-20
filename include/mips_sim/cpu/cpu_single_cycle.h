#ifndef __CPU_SINGLE_CYCLE_H__
#define __CPU_SINGLE_CYCLE_H__

#include <cstdint>

#include "mips_sim/cpu/cpu.h"

class CPU_SingleCycle : public CPU
{
public:
    void process();
    void reset() { pc = 0; }
    bool is_end_of_program()
    {
        uint32_t next_inst = inst_mem.read(pc);
        return next_inst == MEMORY_DEFAULT_VALUE;
    }
};

#endif // __CPU_SINGLE_CYCLE_H__