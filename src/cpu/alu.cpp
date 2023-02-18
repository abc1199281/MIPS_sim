#include <cassert>

#include "mips_sim/cpu/alu.h"
#include "mips_sim/log.h"

//----------------------------------------------------------------------------
void ALU::process(uint32_t in_val1, uint32_t in_val2,
                  Ctrl ALU_Ctrl,
                  uint32_t &out_val, bool &is_zero)
{
    is_zero = false;
    switch (ALU_Ctrl)
    {
    case Ctrl::AND:
        out_val = in_val1 & in_val2;
        L_(ldebug4) << in_val1 << " & " << in_val2;
        break;
    case Ctrl::OR:
        out_val = in_val1 | in_val2;
        L_(ldebug4) << in_val1 << " | " << in_val2;
        break;
    case Ctrl::ADD:
        out_val = in_val1 + in_val2;
        L_(ldebug4) << in_val1 << " + " << in_val2;
        break;
    case Ctrl::SUB:
        out_val = in_val1 - in_val2;
        L_(ldebug4) << in_val1 << " - " << in_val2;
        break;
    case Ctrl::SLT:
        out_val = in_val1 < in_val2 ? 1 : 0;
        L_(ldebug4) << in_val1 << " < " << in_val2 << "?, out= " << out_val;
        break;
    case Ctrl::NOR:
        out_val = ~(in_val1 | in_val2);
        L_(ldebug4) << "~(" << in_val1 << " | " << in_val2 << ") = " << out_val;
        break;
    default:
        L_(lerror) << "not supported ALU_Ctrl";
    }
    is_zero = out_val == 0 ? true : false;
}
//----------------------------------------------------------------------------