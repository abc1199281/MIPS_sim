#ifndef __CPU_PIPELINE_H__
#define __CPU_PIPELINE_H__

#include <cstdint>
#include <list>

#include "mips_sim/cpu/cpu.h"

class CPU_Pipeline : public CPU
{
public:
    void process();
    void reset() { pc = 0; }

    bool is_end_of_program()
    {
        return (MEMORY_DEFAULT_VALUE == inst_mem.read(pc) &&
                reg_IF_ID.empty() &&
                reg_ID_EX.empty() &&
                reg_EX_MEM.empty() &&
                reg_MEM_WB.empty());
    }

private:
    void instruction_fetch();
    void instruction_decode();
    void execution();
    void memory_rw();
    void write_back();

    struct IF_ID
    {
        uint32_t pc;
        uint32_t raw_instruction;
    };
    struct ID_EX
    {
        // original
        uint32_t pc;
        uint32_t reg_out1;
        uint32_t reg_out2;
        uint32_t extended_addr;
        InstructionMemoryUnit::Instruction inst;
        // WB
        // Mem
        // EX
        CtrlSignals ctrl_signals;
    };
    struct EX_MEM
    {
        uint32_t pc;
        uint32_t alu_out;
        uint32_t reg_out2;
        uint32_t reg_idx_w1;
        bool is_zero;
        bool MemWrite;
        bool MemRead;
        bool MemtoReg;
        bool RegWrite;
    };
    struct MEM_WB
    {
        uint32_t pc;
        uint32_t alu_out;
        uint32_t data_mem_out;
        uint32_t reg_idx_w1;
        bool MemtoReg;
        bool RegWrite;
    };

    // pipeline registers
    std::list<IF_ID> reg_IF_ID;
    std::list<ID_EX> reg_ID_EX;
    std::list<EX_MEM> reg_EX_MEM;
    std::list<MEM_WB> reg_MEM_WB;
};

#endif // __CPU_PIPELINE_H__