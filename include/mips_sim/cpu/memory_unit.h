#ifndef __MEMORY_UNIT_H__
#define __MEMORY_UNIT_H__

#include <cstdint>
#include <vector>
#include "mips_sim/log.h"

#define MEMORY_SIZE 2048

// TODO: Memory layout: static, stack, heap, etc.

class MemoryUnit
{
public:
    struct unit
    {
        uint32_t address;
        uint32_t value;
    };
    MemoryUnit();

    std::vector<struct unit> units;
    uint32_t read(uint32_t address);
    void write(uint32_t address, uint32_t value);
};

#endif /* __MEMORY_UNIT_H__ */