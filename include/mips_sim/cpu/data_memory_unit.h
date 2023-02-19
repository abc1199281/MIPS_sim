#ifndef __DATA_MEMORY_UNIT_H__
#define __DATA_MEMORY_UNIT_H__

#include "mips_sim/cpu/memory_unit.h"

class DataMemoryUnit : public MemoryUnit
{
public:
    DataMemoryUnit() = default;
    void process(uint32_t in_address, uint32_t in_value,
                 bool MemWrite, bool MemRead,
                 uint32_t &out_value);
};

#endif /* __DATA_MEMORY_UNIT_H__ */