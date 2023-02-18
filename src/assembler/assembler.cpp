#include <unordered_map>
#include <iostream>
#include <fstream>

#include "mips_sim/log.h"
#include "mips_sim/assembler/assembler.h"
#include "mips_sim/utils.h"

//----------------------------------------------------------------------------
std::unordered_map<std::string, uint8_t> reg_map = {
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

//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
typedef struct R_instruction
{
    uint8_t opcode, rs, rt, rd, shamt, funct;
    uint32_t get()
    {
        uint32_t rtn = 0;
        rtn = pack(rtn, opcode, 26, 6);
        rtn = pack(rtn, rs, 21, 5);
        rtn = pack(rtn, rt, 16, 5);
        rtn = pack(rtn, rd, 11, 5);
        rtn = pack(rtn, shamt, 6, 5);
        rtn = pack(rtn, funct, 0, 6);
        return rtn;
    }
} R_instruction;

//----------------------------------------------------------------------------
typedef struct I_instruction
{
    uint8_t opcode, rs, rt;
    uint16_t const_addr;
    uint32_t get()
    {
        uint32_t rtn = 0;
        rtn = pack(rtn, opcode, 26, 6);
        rtn = pack(rtn, rs, 21, 5);
        rtn = pack(rtn, rt, 16, 5);
        rtn = pack(rtn, const_addr, 0, 16);
        return rtn;
    }
} I_instruction;

//----------------------------------------------------------------------------
uint32_t parse_R_instruct(std::string mnemonic, std::string rs_str, std::string rt_str, std::string rd_str)
{
    R_instruction r_instr;
    r_instr.opcode = mnemonic_parser[mnemonic].opcode;
    r_instr.rs = reg_map[rs_str];
    r_instr.rt = reg_map[rt_str];
    r_instr.rd = reg_map[rd_str];
    r_instr.shamt = 0;
    r_instr.funct = mnemonic_parser[mnemonic].funct;
    return r_instr.get();
}
//----------------------------------------------------------------------------
uint32_t parse_I_instruct(std::string mnemonic, std::string rs_str, std::string rt_str, uint16_t const_addr)
{
    I_instruction i_instr;
    i_instr.opcode = mnemonic_parser[mnemonic].opcode;
    i_instr.rs = reg_map[rs_str];
    i_instr.rt = reg_map[rt_str];
    i_instr.const_addr = const_addr;
    return i_instr.get();
}
//----------------------------------------------------------------------------
uint32_t Assembler::object_code(std::string input)
{
    /*
    TODO: protection
    */
    uint32_t rtn;
    std::vector<std::string> parsed_str = parser.parse(input);
    if (parsed_str.empty())
        return rtn;

    InstructHelper inst_helper = mnemonic_parser[parsed_str[0]];

    switch (inst_helper.format)
    {
    case InstructHelper::Type::R:
        rtn = parse_R_instruct(parsed_str[0], parsed_str[2], parsed_str[3], parsed_str[1]);
        break;
    case InstructHelper::Type::I:
        //  e.g.,lw $t0, 32, $s3:
        // str[0]=lw, str[1]=$t0=rt, str[2]= 32 = const_addr, str[3]=$s3=rs
        rtn = parse_I_instruct(parsed_str[0], parsed_str[3], parsed_str[1], (uint16_t)stoi(parsed_str[2]));
        break;
    default:
        break;
    }

    bin_code.push_back(rtn);
    return rtn;
}

//----------------------------------------------------------------------------
void Assembler::load(std::string infile_name)
{
    std::ifstream infile(infile_name);
    if(!infile.is_open())
        L_(lerror)<<"infile is not open, with file name: "<< infile_name;

    std::string line;
    while (std::getline(infile, line))
    {
        bin_code.push_back(object_code(line));
    }
}

//----------------------------------------------------------------------------
void Assembler::save(std::string outfile_name)
{
    std::ofstream outfile(outfile_name, std::ios::binary);
    if(!outfile.is_open())
        L_(lerror)<<"outfile is not open, with file name: "<< outfile_name;

    while(!bin_code.empty()){
        uint32_t num = bin_code.front();
        outfile.write(reinterpret_cast<const char *>(&num), sizeof(num));
        bin_code.pop_front();
    }
}
