#include <unordered_map>

#include "mips_sim/cpu/cpu_pipeline.h"
#include "mips_sim/utils.h"
#include "mips_sim/log.h"

//----------------------------------------------------------------------------
void CPU_Pipeline::process()
{
    instruction_fetch();
    instruction_decode();
    execution();
    memory_rw();
    write_back();
}
//----------------------------------------------------------------------------
void CPU_Pipeline::instruction_fetch()
{
    uint32_t inst = inst_mem.read(pc);
    pc += 4;
    reg_IF_ID.push_back(
        {pc,
         inst});
}
//----------------------------------------------------------------------------
void CPU_Pipeline::instruction_decode()
{
    if (!reg_IF_ID.empty())
    {
        return;
    }
    IF_ID if_id = reg_IF_ID.front();
    reg_IF_ID.pop_front();

    InstructionMemoryUnit::Instruction inst(if_id.raw_instruction);

    CtrlSignals ctrl_signals = ctrl(inst.opcode);

    uint32_t extend_addr = sign_extension(inst.address);

    // Decode and register file (read)
    uint8_t reg_idx_r1 = inst.rs;
    uint8_t reg_idx_r2 = inst.rt;
    uint32_t reg_out1, reg_out2;
    reg_file.read(reg_idx_r1, reg_idx_r2,
                  reg_out1, reg_out2);

    L_(ldebug4) << "reg_idx_r1: " << int(reg_idx_r1) << ", reg_idx_r2: " << int(reg_idx_r2);
    L_(ldebug4) << "reg_out1: " << int(reg_out1) << ", reg_out2: " << int(reg_out2) << std::endl;

    reg_ID_EX.push_back(
        {pc,
         reg_out1,
         reg_out2,
         extend_addr,
         inst,
         ctrl_signals});
}
//----------------------------------------------------------------------------
void CPU_Pipeline::execution()
{
    if (!reg_ID_EX.empty())
    {
        return;
    }
    ID_EX id_ex = reg_ID_EX.front();
    reg_ID_EX.pop_front();

    // ALU Ctrl
    ALU::Ctrl ALU_Ctrl = alu_ctrl(id_ex.inst.funct,
                                  id_ex.ctrl_signals.ALU_Op);

    // Execution
    uint32_t alu_in1 = id_ex.reg_out1;
    uint32_t alu_in2 = multiplier_2to1(id_ex.ctrl_signals.ALUSrc,
                                       id_ex.extended_addr,
                                       id_ex.reg_out2);
    bool is_zero;
    uint32_t alu_out;
    alu.execute(alu_in1, alu_in2, ALU_Ctrl, alu_out, is_zero);
    L_(ldebug4) << "alu_in1: " << int(alu_in1) << ", alu_in2: " << int(alu_in2);
    L_(ldebug4) << "alu_out: " << int(alu_out) << ", is_zero:" << is_zero << std::endl;

    // RegDst
    uint8_t reg_idx_w1 = multiplier_2to1(id_ex.ctrl_signals.RegDst,
                                         id_ex.inst.rd,
                                         id_ex.inst.rt);
    reg_EX_MEM.push_back(
        {pc,
         alu_out,
         id_ex.reg_out2,
         reg_idx_w1,
         is_zero,
         id_ex.ctrl_signals.MemWrite,
         id_ex.ctrl_signals.MemRead,
         id_ex.ctrl_signals.MemtoReg,
         id_ex.ctrl_signals.RegWrite});
}
//----------------------------------------------------------------------------
void CPU_Pipeline::memory_rw()
{
    if (!reg_EX_MEM.empty())
    {
        return;
    }
    EX_MEM ex_mem = reg_EX_MEM.front();
    reg_EX_MEM.pop_front();

    // Data memory
    uint32_t in_address = ex_mem.alu_out;
    uint32_t in_value = ex_mem.reg_out2;
    uint32_t data_mem_out;
    data_mem.process(in_address, in_value,
                     ex_mem.MemWrite, ex_mem.MemRead,
                     data_mem_out);
    L_(ldebug4) << "in_address: " << int(in_address) << ", in_value: " << int(in_value);
    L_(ldebug4) << "ctrl_signals.MemWrite: " << int(ex_mem.MemWrite) << ", ctrl_signals.MemRead: " << int(ex_mem.MemRead);
    L_(ldebug4) << "data_mem_out: " << int(data_mem_out) << std::endl;

    reg_MEM_WB.push_back(
        {pc,
         ex_mem.alu_out,
         data_mem_out,
         ex_mem.reg_idx_w1,
         ex_mem.MemtoReg,
         ex_mem.RegWrite});
}
//----------------------------------------------------------------------------
void CPU_Pipeline::write_back()
{
    if (!reg_MEM_WB.empty())
    {
        return;
    }
    MEM_WB ex_mem = reg_MEM_WB.front();
    reg_MEM_WB.pop_front();

    // final multiplier
    uint32_t cpu_out = multiplier_2to1(ex_mem.MemtoReg,
                                       ex_mem.data_mem_out,
                                       ex_mem.alu_out);

    // register file (write back)
    uint8_t reg_idx_w1 = ex_mem.reg_idx_w1;
    uint8_t reg_in_val = cpu_out;
    reg_file.write(reg_idx_w1, reg_in_val, ex_mem.RegWrite);
    L_(ldebug4) << "reg_idx_w1: " << int(reg_idx_w1) << ", reg_in_val: " << int(reg_in_val);
    L_(ldebug4) << "ctrl_signals.RegWrite: " << int(ex_mem.RegWrite) << std::endl
                << std::endl;
}
//----------------------------------------------------------------------------