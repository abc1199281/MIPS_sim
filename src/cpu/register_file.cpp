#include "mips_sim/cpu/register_file.h"

//----------------------------------------------------------------------------
RegisterFile::RegisterFile()
{
    registers = {
        {false, "$zero", 0},
        {false, "$at", 0},
        {false, "$v0", 0},
        {false, "$v1", 0},
        {false, "$a0", 0},
        {false, "$a1", 0},
        {false, "$a2", 0},
        {false, "$a3", 0},
        {false, "$t0", 0},
        {false, "$t1", 0},
        {false, "$t2", 0},
        {false, "$t3", 0},
        {false, "$t4", 0},
        {false, "$t5", 0},
        {false, "$t6", 0},
        {false, "$t7", 0},
        {true, "$s0", 0},
        {true, "$s1", 0},
        {true, "$s2", 0},
        {true, "$s3", 0},
        {true, "$s4", 0},
        {true, "$s5", 0},
        {true, "$s6", 0},
        {true, "$s7", 0},
        {false, "$t8", 0},
        {false, "$t9", 0},
        {false, "$k0", 0},
        {false, "$k1", 0},
        {true, "$gp", 0},
        {true, "$sp", 0},
        {true, "$fp", 0},
        {false, "$ra", 0}};
}

//----------------------------------------------------------------------------
void RegisterFile::read(uint8_t in_r1_idx, uint8_t in_r2_idx,
                        uint32_t &out_val1, uint32_t &out_val2)
{
    out_val1 = read(in_r1_idx);
    out_val2 = read(in_r2_idx);
}
//----------------------------------------------------------------------------
void RegisterFile::write(uint8_t in_w_idx, uint32_t in_val, bool ctrl_reg_write)
{
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

void RegisterFile::show(bool skip_zero)
{
    for (int i = 0; i < registers.size(); i++)
    {
        if (skip_zero && registers[i].value == 0)
            continue;
        L_(linfo) << registers[i].name << ": " << registers[i].value;
    }
};

//----------------------------------------------------------------------------