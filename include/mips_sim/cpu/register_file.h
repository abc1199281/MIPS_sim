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
        std::string name;
        uint32_t value;
    } Register;

    void process_read(uint8_t in_r1_idx, uint8_t in_r2_idx,
                      uint32_t &out_val1, uint32_t &out_val2);
    void process_write(uint8_t in_w_idx, uint32_t in_val, bool ctrl_reg_write);
    void show(bool skip_zero = true);

private:
    static std::vector<Register> registers;
    uint32_t read(uint32_t index);
    void write(uint32_t index, uint32_t value);
    bool reg_write_state = false;
};

#endif // __REGISTER_FILE_H__