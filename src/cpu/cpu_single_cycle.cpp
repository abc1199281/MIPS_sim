#include <unordered_map>

#include "mips_sim/cpu/cpu_single_cycle.h"
#include "mips_sim/utils.h"
#include "mips_sim/log.h"

//----------------------------------------------------------------------------
void CPU_SingleCycle::process()
{
    // fetch instruction
    InstructionMemoryUnit::Instruction inst = inst_mem.fetch(pc);

    // Ctrl Unit
    CtrlSignals ctrl_signals = ctrl(inst.opcode);

    // sign extension
    uint32_t extend_addr = sign_extension(inst.address);

    // ALU Ctrl
    ALU::Ctrl ALU_Ctrl = alu_ctrl(inst.funct, ctrl_signals.ALU_Op);

    // register file
    uint8_t reg_idx_r1 = inst.rs;
    uint8_t reg_idx_r2 = inst.rt;
    uint8_t reg_idx_w1 = multiplier_2to1(ctrl_signals.RegDst, inst.rd, inst.rt);
    uint8_t reg_in_val = cpu_out; // previous cpu out
    uint32_t reg_out1, reg_out2;
    reg_file.process(reg_idx_r1, reg_idx_r2, reg_idx_w1, reg_in_val,
                     ctrl_signals.RegWrite,
                     reg_out1, reg_out2);

    // ALU
    uint32_t alu_in1 = reg_out1;
    uint32_t alu_in2 = multiplier_2to1(ctrl_signals.ALUSrc, extend_addr, reg_out2);
    bool is_zero;
    uint32_t alu_out;
    alu.process(alu_in1, alu_in2, ALU_Ctrl, alu_out, is_zero);

    // data memory
    uint32_t in_address = alu_out;
    uint32_t in_value = reg_out2;
    uint32_t data_mem_out;
    data_mem.process(in_address, in_value,
                     ctrl_signals.MemWrite, ctrl_signals.MemRead,
                     data_mem_out);

    // final multiplier
    cpu_out = multiplier_2to1(ctrl_signals.MemtoReg, data_mem_out, alu_out);

    // Update program counter
    pc += 4;
    uint32_t br_addr_out = extend_addr << 2 + pc;
    bool PCSrc = ctrl_signals.Branch && is_zero;
    pc = multiplier_2to1(PCSrc, pc, br_addr_out);
}

//----------------------------------------------------------------------------
ALU::Ctrl CPU_SingleCycle::alu_ctrl(uint8_t funct, uint8_t ALU_Op)
{
    static std::unordered_map<uint8_t, uint8_t> funct_map = {
        {0b0000, 0b0010},
        {0b0010, 0b0110},
        {0b0100, 0b0000},
        {0b0101, 0b0001},
        {0b1010, 0b0111},
    };
    uint8_t sub_funct = funct & B2M(4); // only four bits matter.
    if (funct_map.find(sub_funct) == funct_map.end())
    {
        L_(lerror) << "Error: no function code found in cpu::alu_ctrl";
        return ALU::Ctrl();
    }
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
    return static_cast<ALU::Ctrl>(ALU_map[ALU_Op]);
}

//----------------------------------------------------------------------------
CPU_SingleCycle::CtrlSignals CPU_SingleCycle::ctrl(uint8_t opcode)
{
    static std::unordered_map<uint8_t, uint16_t> opcode_map = {
        {0b000000, 0b100100010},
        {0b100011, 0b011110000},
        {0b101011, 0b010001000},
        {0b000100, 0b000000101}};

    if (opcode_map.find(opcode) == opcode_map.end())
    {
        L_(lerror) << "Error: no opcode found in cpu::ctrl";
        return CtrlSignals(0);
    }
    return CtrlSignals(opcode_map[opcode]);
}
//----------------------------------------------------------------------------