#include <unordered_map>

#include "mips_sim/cpu/cpu.h"
#include "mips_sim/utils.h"
#include "mips_sim/log.h"

//----------------------------------------------------------------------------
ALU::Ctrl CPU::alu_ctrl(uint8_t funct, uint8_t ALU_Op)
{
    // Figure 4.13
    static std::unordered_map<uint8_t, uint8_t> funct_map = {
        {0b0000, 0b0010},
        {0b0010, 0b0110},
        {0b0100, 0b0000},
        {0b0101, 0b0001},
        {0b1010, 0b0111},
    };
    uint8_t sub_funct = funct & B2M(4); // only four bits matter.
    std::unordered_map<uint8_t, uint8_t> ALU_map = {
        {0b00, 0b0010},
        {0b01, 0b0110},
        {0b11, 0b0110},
        {0b10, funct_map[sub_funct]}};

    if (ALU_map.find(ALU_Op) == ALU_map.end())
    {
        L_(lerror) << "Error: no ALU_Op found in cpu::alu_ctrl";
        return ALU::Ctrl();
    }
    if (ALU_Op == 0b10 && funct_map.find(sub_funct) == funct_map.end())
    {
        L_(lerror) << "Error: no function code found in cpu::alu_ctrl:" << int(sub_funct);
        return ALU::Ctrl();
    }
    return static_cast<ALU::Ctrl>(ALU_map[ALU_Op]);
}

//----------------------------------------------------------------------------
CPU::CtrlSignals CPU::ctrl(uint8_t opcode)
{
    // Figure 4.22
    static std::unordered_map<uint8_t, uint16_t> opcode_map = {
        {0b000000, 0b0100100010},
        {0b100011, 0b0011110000},
        {0b101011, 0b0010001000},
        {0b000100, 0b0000000101},
        {0b000010, 0b1000000000}};

    if (opcode_map.find(opcode) == opcode_map.end())
    {
        L_(lerror) << "Error: no opcode found in cpu::ctrl:" << std::dec << int(opcode);
        return CtrlSignals(0);
    }
    return CtrlSignals(opcode_map[opcode]);
}
//----------------------------------------------------------------------------