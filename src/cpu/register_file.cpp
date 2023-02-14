#include "mips_sim/cpu/register_file.h"

//----------------------------------------------------------------------------
void RegisterFile::process(uint8_t in_r1_idx, uint8_t in_r2_idx, uint8_t in_w_idx, uint32_t in_val,
                           bool ctrl_reg_write,
                           uint32_t &out_val1, uint32_t &out_val2)
{
    out_val1 = read(in_r1_idx);
    out_val2 = read(in_r2_idx);
    if (ctrl_reg_write)
        write(in_w_idx, in_val);
}

//----------------------------------------------------------------------------
uint32_t RegisterFile::read(uint32_t index)
{
    if (index < 0 || index >= 32)
    {
        L_(lerror) << "index out of range: " << index << ", with range: 0~32";
    }
    return registers[index].value;
};

//----------------------------------------------------------------------------
void RegisterFile::write(uint32_t index, uint32_t value)
{
    if (index < 0 || index >= 32)
    {
        L_(lerror) << "index out of range: " << index << ", with range: 0~32";
    }
    registers[index].value = value;
};

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------