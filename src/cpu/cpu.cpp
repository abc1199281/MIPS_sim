
#include "mips_sim/cpu/cpu.h"
#include "mips_sim/utils.h"

//----------------------------------------------------------------------------
void CPU::process()
{
    // Ctrl flags
    bool RegWrite = false;
    bool ALUSrc = false;
    uint8_t ALU_Ctrl;
    bool MemRead = false;
    bool MemWrite = false;
    bool MemToReg = false;
    bool PCSrc = false;

    // instruction memory
    uint32_t instruction_out;
    inst_mem.process(pc, instruction_out);

    // TODO: instruction to registers.

    // sign extension
    uint32_t extend_addr = sign_extension((uint16_t)instruction_out);

    // register file
    uint8_t reg_idx_r1, reg_idx_r2, reg_idx_w1;
    uint8_t reg_in_val = cpu_out; // previous cpu out
    uint32_t reg_val1, reg_val2;
    reg_file.process(reg_idx_r1, reg_idx_r2, reg_idx_w1, reg_in_val,
                     RegWrite, reg_val1, reg_val2);

    // ALU
    uint32_t alu_in1 = reg_val1;
    uint32_t alu_in2 = multiplier_2to1(ALUSrc, reg_val1, extend_addr);
    bool is_zero;
    uint32_t alu_out;
    alu.process(alu_in1, alu_in2, ALU_Ctrl, alu_out, is_zero);

    // data memory
    uint32_t in_address = alu_out;
    uint32_t in_value = reg_val2;
    uint32_t data_mem_out;
    data_mem.process(in_address, in_value, MemWrite, MemRead, data_mem_out);

    // final multiplier
    cpu_out = multiplier_2to1(MemToReg, data_mem_out, alu_out);

    // adder: program counter
    pc += 4;

    // adder: branch
    uint32_t br_addr_out = extend_addr << 2 + pc;

    // multiplier
    pc = multiplier_2to1(PCSrc, pc, br_addr_out);
}
//----------------------------------------------------------------------------