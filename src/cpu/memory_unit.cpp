#include "mips_sim/cpu/memory_unit.h"

//----------------------------------------------------------------------------
MemoryUnit::MemoryUnit() : units(MEMORY_SIZE)
{
    uint32_t cnt = 0;
    for (auto ele : units)
    {
        ele.address = cnt;
        cnt += 4;
    }
};

//----------------------------------------------------------------------------
uint32_t MemoryUnit::read(uint32_t address)
{
    if (address < 0 || address > units.back().address)
    {
        L_(lerror) << "address out of range: " << address << ", with range: " << units.back().address;
        return 0;
    }
    return units[address / 4].value;
}

//----------------------------------------------------------------------------
void MemoryUnit::write(uint32_t address, uint32_t value)
{
    if (address < 0 || address > units.back().address)
    {
        L_(lerror) << "address out of range: " << address << ", with range: " << units.back().address;
    }
    units[address / 4].value = value;
}
//----------------------------------------------------------------------------