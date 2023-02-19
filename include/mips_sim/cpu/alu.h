#ifndef __ALU_H__
#define __ALU_H__

#include <cstdint>

class ALU{
public:
    enum class Ctrl : uint8_t
    {
        AND = 0b0000,
        OR = 0b0001,
        ADD = 0b0010,
        SUB = 0b0110,
        SLT = 0b0111,
        NOR = 0b1100
    };
    void execute(uint32_t in_val1, uint32_t in_val2,
                 Ctrl ALU_Ctrl,
                 uint32_t &out_val, bool &is_zero);
};

#endif // __ALU_H__