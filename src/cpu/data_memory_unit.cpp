#include "mips_sim/cpu/data_memory_unit.h"
#include "mips_sim/log.h"

//----------------------------------------------------------------------------
void DataMemoryUnit::process(uint32_t in_address, uint32_t in_value,
                             bool MemWrite, bool MemRead,
                             uint32_t &out_value)
{
    if (MemWrite)
        write(in_address, in_value);
    if (MemRead)
        out_value = read(in_address);

    L_(ldebug4) << "in_address:" << in_address << ", in_value:" << in_value;
    L_(ldebug4) << "MemW:" << MemWrite << ", MemR:" << MemRead;
    L_(ldebug4) << "out_value:" << out_value;
};

//----------------------------------------------------------------------------