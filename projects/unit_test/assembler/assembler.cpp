#include <catch2/catch.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "unit_test/data_path.h"
#include "mips_sim/assembler/assembler.h"

//----------------------------------------------------------------------------
TEST_CASE("R instruct", "[assembler]")
{
    Assembler Assembler;
    std::string test_input = "add $t0 , $s2, $t0 # comments";
    uint32_t expected_output_bin = 0b00000010010010000100000000100000;
    uint32_t rtn_bin = Assembler.object_code(test_input);
    REQUIRE(expected_output_bin == rtn_bin);
}
//----------------------------------------------------------------------------

TEST_CASE("I instruct", "[assembler]")
{
    Assembler Assembler;
    std::string test_input = "lw $t0, $t1 , 1200 # comments";
    uint32_t expected_output_bin = 0b10001101001010000000010010110000;
    uint32_t rtn_bin = Assembler.object_code(test_input);
    REQUIRE(expected_output_bin == rtn_bin);
}
//----------------------------------------------------------------------------

TEST_CASE("load data", "[assembler]")
{
    Assembler Assembler;
    std::string test_input_file = std::string(IN_DATA_PATH)+"/assembler/in.asm";
    std::string test_output_file = std::string(IN_DATA_PATH) + "/assembler/out.o";
    uint32_t expected_output_bin = 0b00000010010010000100000000100000;
    Assembler.load(test_input_file);
    Assembler.save(test_output_file);

    std::ifstream infile(test_output_file, std::ios::binary);
    char *buffer = new char[4];
    infile.read(buffer, sizeof(uint32_t));
    const uint32_t *output_num = reinterpret_cast<const uint32_t*>(buffer);
    REQUIRE(*output_num==expected_output_bin);
    delete[] buffer;
    //REQUIRE(expected_output_bin == rtn_bin);
}
//----------------------------------------------------------------------------
