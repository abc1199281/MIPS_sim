#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>

typedef struct Register
{
    // std::string name;
    // uint8_t number;
    bool preserved_across_call;
    std::string use;
} Register;

static std::vector<Register> registers = {
    {false, "$zero"},
    {false, "$at"},
    {false, "$v0"},
    {false, "$v1"},
    {false, "$a0"},
    {false, "$a1"},
    {false, "$a2"},
    {false, "$a3"},
    {false, "$t0"},
    {false, "$t1"},
    {false, "$t2"},
    {false, "$t3"},
    {false, "$t4"},
    {false, "$t5"},
    {false, "$t6"},
    {false, "$t7"},
    {true, "$s0"},
    {true, "$s1"},
    {true, "$s2"},
    {true, "$s3"},
    {true, "$s4"},
    {true, "$s5"},
    {true, "$s6"},
    {true, "$s7"},
    {false, "$t8"},
    {false, "$t9"},
    {false, "$k0"},
    {false, "$k1"},
    {true, "$gp"},
    {true, "$sp"},
    {true, "$fp"},
    {false, "$ra"}};

/*
std::unordered_map<std::string, Register>
    registers = {
        {"$zero", {"$zero", 0, false, "The Constant Value 0"}}, 
        {"$at", {"$at", 1, false, "Assembler Temporary"}}, 
        {"$v0", {"$v0", 2, false, "Values for Function Results and Expression Evaluation"}}, 
        {"$v1", {"$v1", 3, false, "Values for Function Results and Expression Evaluation"}}, 
        {"$a0", {"$a0", 4, false, "Arguments"}}, 
        {"$a1", {"$a1", 5, false, "Arguments"}}, 
        {"$a2", {"$a2", 6, false, "Arguments"}}, 
        {"$a3", {"$a3", 7, false, "Arguments"}}, 
        {"$t0", {"$t0", 8, false, "Temporaries"}}, 
        {"$t1", {"$t1", 9, false, "Temporaries"}}, 
        {"$t2", {"$t2", 10, false, "Temporaries"}}, 
        {"$t3", {"$t3", 11, false, "Temporaries"}}, 
        {"$t4", {"$t4", 12, false, "Temporaries"}}, 
        {"$t5", {"$t5", 13, false, "Temporaries"}}, 
        {"$t6", {"$t6", 14, false, "Temporaries"}}, 
        {"$t7", {"$t7", 15, false, "Temporaries"}}, 
        {"$s0", {"$s0", 16, true, "Saved Temporaries"}},
        {"$s1", {"$s1", 17, true, "Saved Temporaries"}}, 
        {"$s2", {"$s2", 18, true, "Saved Temporaries"}}, 
        {"$s3", {"$s3", 19, true, "Saved Temporaries"}}, 
        {"$s4", {"$s4", 20, true, "Saved Temporaries"}}, 
        {"$s5", {"$s5", 21, true, "Saved Temporaries"}}, 
        {"$s6", {"$s6", 22, true, "Saved Temporaries"}}, 
        {"$s7", {"$s7", 23, true, "Saved Temporaries"}}, 
        {"$t8", {"$t8", 24, false, "Temporaries"}}, 
        {"$t8", {"$t8", 25, false, "Temporaries"}}, 
        {"$k0", {"$k0", 26, false, "Reversed for OS Kernel"}}, 
        {"$k1", {"$k1", 27, false, "Reversed for OS Kernel"}}, 
        {"$gp", {"$gp", 28, true, "Global Pointer"}}, 
        {"$sp", {"$sp", 29, true, "Stack Pointer"}}, 
        {"$fp", {"$fp", 30, true, "Frame Pointer"}}, 
        {"$ra", {"$ra", 31, false, "Return Address"}}};
*/
#endif // __REGISTER_H__