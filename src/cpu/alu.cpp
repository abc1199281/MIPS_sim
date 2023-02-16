#include <cassert>

#include "mips_sim/cpu/alu.h"

//----------------------------------------------------------------------------
void ALU::process(uint32_t in_val1, uint32_t in_val2,
                  Ctrl ALU_Ctrl,
                  uint32_t out_val, bool &is_zero)
{
    /**
     * Multi-layer decode:
     * 1. Control Unit: generate ALU_Op
     * 2. ALU Control Unit: generate ALU Ctrl
     */
    // Multi-layer decode:
    // 1. Control Unit: generate ALU_Op
    // 2.
}
//----------------------------------------------------------------------------