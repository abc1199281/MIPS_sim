#include <unordered_map>

#include "mips_sim/cpu/cpu_single_cycle.h"
#include "mips_sim/utils.h"
#include "mips_sim/log.h"

//----------------------------------------------------------------------------
void CPU_SingleCycle::process()
{
    // Fetch instruction
    InstructionMemoryUnit::Instruction inst = inst_mem.fetch(pc);

    // Ctrl Units
    CtrlSignals ctrl_signals = ctrl(inst.opcode);
    // sign extension
    uint32_t extend_addr = sign_extension(inst.address);
    // ALU Ctrl
    ALU::Ctrl ALU_Ctrl = alu_ctrl(inst.funct, ctrl_signals.ALU_Op);

    // Decode and register file (read)
    uint8_t reg_idx_r1 = inst.rs;
    uint8_t reg_idx_r2 = inst.rt;
    uint32_t reg_out1, reg_out2;
    reg_file.read(reg_idx_r1, reg_idx_r2,
                  reg_out1, reg_out2);

    L_(ldebug4) << "reg_idx_r1: " << int(reg_idx_r1) << ", reg_idx_r2: " << int(reg_idx_r2);
    L_(ldebug4) << "reg_out1: " << int(reg_out1) << ", reg_out2: " << int(reg_out2) << std::endl;

    // Execution
    uint32_t alu_in1 = reg_out1;
    uint32_t alu_in2 = multiplier_2to1(ctrl_signals.ALUSrc, extend_addr, reg_out2);
    bool is_zero;
    uint32_t alu_out;
    alu.execute(alu_in1, alu_in2, ALU_Ctrl, alu_out, is_zero);
    L_(ldebug4) << "alu_in1: " << int(alu_in1) << ", alu_in2: " << int(alu_in2);
    L_(ldebug4) << "alu_out: " << int(alu_out) << ", is_zero:" << is_zero << std::endl;

    // Data memory
    uint32_t in_address = alu_out;
    uint32_t in_value = reg_out2;
    uint32_t data_mem_out;
    data_mem.process(in_address, in_value,
                     ctrl_signals.MemWrite, ctrl_signals.MemRead,
                     data_mem_out);
    L_(ldebug4) << "in_address: " << int(in_address) << ", in_value: " << int(in_value);
    L_(ldebug4) << "ctrl_signals.MemWrite: " << int(ctrl_signals.MemWrite) << ", ctrl_signals.MemRead: " << int(ctrl_signals.MemRead);
    L_(ldebug4) << "data_mem_out: " << int(data_mem_out) << std::endl;

    // Update program counter
    uint32_t pc_add4 = pc + 4;
    uint32_t br_addr_out = (extend_addr << 2) + pc_add4;
    bool PCSrc = ctrl_signals.Branch && is_zero;
    uint32_t jump_address = (inst.long_address << 2) | (unpack(pc_add4, 28, 4) << 28);
    pc = multiplier_2to1(PCSrc, br_addr_out, pc_add4);
    pc = multiplier_2to1(ctrl_signals.Jump, jump_address, pc);

    L_(ldebug4) << "ctrl_signals.Branch: " << ctrl_signals.Branch << ", is_zero: " << is_zero;
    L_(ldebug4) << "PCSrc: " << PCSrc << ", pc_add4: " << pc_add4 << ", br_addr_out: " << br_addr_out;
    L_(ldebug4) << "ctrl_signals.Jump: " << ctrl_signals.Jump << ", jump_address: " << jump_address;
    L_(ldebug4) << "PC= " << pc;

    // final multiplier
    uint32_t cpu_out = multiplier_2to1(ctrl_signals.MemtoReg, data_mem_out, alu_out);

    // register file (write back)
    uint8_t reg_idx_w1 = multiplier_2to1(ctrl_signals.RegDst, inst.rd, inst.rt);
    uint8_t reg_in_val = cpu_out;
    reg_file.write(reg_idx_w1, reg_in_val, ctrl_signals.RegWrite);
    L_(ldebug4) << "reg_idx_w1: " << int(reg_idx_w1) << ", reg_in_val: " << int(reg_in_val);
    L_(ldebug4) << "ctrl_signals.RegWrite: " << int(ctrl_signals.RegWrite) << std::endl
                << std::endl;
}