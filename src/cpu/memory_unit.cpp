#include <iostream>

#include "mips_sim/cpu/memory_unit.h"

//----------------------------------------------------------------------------
MemoryUnit::MemoryUnit() : units(MEMORY_SIZE)
{
    uint32_t cnt = 0;
    for (uint32_t i = 0; i < MEMORY_SIZE; i++)
    {
        units[i].address = i << 2;
        units[i].value = MEMORY_DEFAULT_VALUE;
    }
};

//----------------------------------------------------------------------------
uint32_t MemoryUnit::read(uint32_t address)
{
    if (address < 0 || address > units.back().address)
    {
        L_(lerror) << "address out of range: " << std::hex << address << ", with range: " << units.back().address;
        return MEMORY_DEFAULT_VALUE;
    }
    return units[address / 4].value;
}

//----------------------------------------------------------------------------
void MemoryUnit::write(uint32_t address, uint32_t value)
{
    L_(ldebug4) << std::hex << "address:" << address << ", value: " << value;
    if (address < 0 || address > units.back().address)
    {
        L_(lerror) << "address out of range: " << address << ", with range: " << units.back().address;
    }
    units[address / 4].value = value;
}
//----------------------------------------------------------------------------
void MemoryUnit::show(bool hide_default)
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        if (!hide_default || units[i].value != MEMORY_DEFAULT_VALUE)
            L_(linfo) << "address: " << units[i].address << ", value: " << units[i].value;
    }
}
//----------------------------------------------------------------------------