#ifndef __REGISTER_FILE_H__
#define __REGISTER_FILE_H__

#include <string>
#include <vector>

#include "mips_sim/log.h"

class RegisterFile
{
public:
    typedef struct Register
    {
        bool preserved_across_call;
        std::string use; // incase
        uint32_t value;
    } Register;

    void process(uint8_t in_r1_idx, uint8_t in_r2_idx, uint8_t in_w_idx, uint32_t in_val,
                 bool ctrl_reg_write,
                 uint32_t &out_val1, uint32_t &out_val2);

private:
    static std::vector<Register> registers;
    uint32_t read(uint32_t index);
    void write(uint32_t index, uint32_t value);
};

static std::vector<RegisterFile::Register> registers = {
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

#endif // __REGISTER_FILE_H__