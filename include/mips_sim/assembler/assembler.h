#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <string>
#include <list>
#include <cstdint>
#include <unordered_map>
#include "mips_sim/assembler/parser.h"

class Assembler
{
public:
    void load(std::string in_file);
    void save(std::string out_file);
    std::list<uint32_t> get_obj_code()
    {
        return obj_code;
    };

    // TODO: how to move these functions into private while keeping unit test?
    uint32_t object_code(std::string input);
    void label_code(std::string input);

private:
    Parser parser;
    Parser parser_label;
    uint16_t pseudo_pc; // pseudo_pc
    std::list<uint32_t> obj_code;

    std::unordered_map<std::string, uint16_t> label_map;
    bool is_label(std::string str);

    uint32_t parse_I_instruct(std::string mnemonic, std::string rs_str,
                              std::string rt_str, uint16_t const_addr);
};

#endif // __ASSEMBLER_H__