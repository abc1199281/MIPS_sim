#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <string>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <regex>

#include "mips_sim/instruction.h"
#include "mips_sim/register.h"

class Assembler
{
};

typedef struct InstructHelper
{
    enum class Type : uint8_t
    {
        R,
        I,
        J,
        FI,
        FR
    };
    Type format;
    uint8_t opcode;
    uint8_t funct;
} InstructHelper;

// Instruction to opcode (function code)
std::unordered_map<std::string, InstructHelper> mnemonic_parser = {
    {"add", {InstructHelper::Type::R, 0x00, 0x20}},
    {"addi", {InstructHelper::Type::I, 0x08}},
    {"addiu", {InstructHelper::Type::I, 0x09}},
    {"addu", {InstructHelper::Type::R, 0x00, 0x21}},
    {"and", {InstructHelper::Type::R, 0x00, 0x24}},
    {"andi", {InstructHelper::Type::I, 0x0c}},
    {"beq", {InstructHelper::Type::I, 0x04}},
    {"bne", {InstructHelper::Type::I, 0x05}},
    {"j", {InstructHelper::Type::I, 0x02}},
    {"jal", {InstructHelper::Type::I, 0x03}},
    {"jr", {InstructHelper::Type::R, 0x00, 0x08}},
    {"lbu", {InstructHelper::Type::I, 0x24}},
    {"lhu", {InstructHelper::Type::I, 0x25}},
    {"ll", {InstructHelper::Type::I, 0x30}},
    {"lui", {InstructHelper::Type::I, 0x0f}},
    {"lw", {InstructHelper::Type::I, 0x23}},
    {"nor", {InstructHelper::Type::R, 0x00, 0x27}},
    {"or", {InstructHelper::Type::R, 0x00, 0x25}},
    {"ori", {InstructHelper::Type::I, 0x0d}},
    {"slt", {InstructHelper::Type::R, 0x00, 0x2a}},
    {"slti", {InstructHelper::Type::I, 0x0a}},
    {"sltiu", {InstructHelper::Type::I, 0x0b}},
    {"sltu", {InstructHelper::Type::R, 0x00, 0x2b}},
    {"sll", {InstructHelper::Type::R, 0x00, 0x00}},
    {"srl", {InstructHelper::Type::R, 0x00, 0x02}},
    {"sb", {InstructHelper::Type::I, 0x28}},
    {"sc", {InstructHelper::Type::I, 0x38}},
    {"sh", {InstructHelper::Type::I, 0x29}},
    {"sw", {InstructHelper::Type::I, 0x2b}},
    {"sub", {InstructHelper::Type::R, 0x00, 0x22}},
    {"subu", {InstructHelper::Type::R, 0x00, 0x23}}};

std::unordered_map<std::string, uint8_t> reg_parser = {
    {"$zero", 0},
    {"$at", 1},
    {"$v0", 2},
    {"$v1", 3},
    {"$a0", 4},
    {"$a1", 5},
    {"$a2", 6},
    {"$a3", 7},
    {"$t0", 8},
    {"$t1", 9},
    {"$t2", 10},
    {"$t3", 11},
    {"$t4", 12},
    {"$t5", 13},
    {"$t6", 14},
    {"$t7", 15},
    {"$s0", 16},
    {"$s1", 17},
    {"$s2", 18},
    {"$s3", 19},
    {"$s4", 20},
    {"$s5", 21},
    {"$s6", 22},
    {"$s7", 23},
    {"$t8", 24},
    {"$t9", 25},
    {"$k0", 26},
    {"$k1", 27},
    {"$gp", 28},
    {"$sp", 29},
    {"$fp", 30},
    {"$ra", 31}};

InstructHelper::Type get_instruct_type(std::string mnemonic)
{
    return InstructHelper(mnemonic_parser[mnemonic]).format;
}

uint32_t parse_R_instruct(std::string mnemonic, std::string rs_str, std::string rt_str, std::string rd_str)
{
    uint32_t rtn = 0;
    R_Instruction r_instr(0);
    r_instr.opcode = mnemonic_parser[mnemonic].opcode;
    r_instr.funct = mnemonic_parser[mnemonic].funct;
    r_instr.rs = reg_parser[rs_str];
    r_instr.rt = reg_parser[rt_str];
    r_instr.rd = reg_parser[rd_str];
    std::cout << std::hex << (uint)r_instr.opcode << std::endl;
    std::cout << std::hex << (uint)r_instr.funct << std::endl;
    std::cout << std::hex << (uint)r_instr.rs << std::endl;
    std::cout << std::hex << (uint)r_instr.rt << std::endl;
    std::cout << std::hex << (uint)r_instr.rd << std::endl;
    return r_instr.get();
}

#endif // __ASSEMBLER_H__