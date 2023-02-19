#include <catch2/catch.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "unit_test/data_path.h"
#include "mips_sim/assembler/assembler.h"
#include "mips_sim/cpu/cpu_single_cycle.h"

//----------------------------------------------------------------------------
TEST_CASE("show_data_mem", "[cpu]")
{
    CPU_SingleCycle cpu;
    Assembler Assembler;

    // Generate object code
    std::string test_input_file = std::string(IN_DATA_PATH) + "/cpu/in.asm";
    std::string test_output_file = std::string(OUT_DATA_PATH) + "/cpu/out.o";
    Assembler.load(test_input_file);
    Assembler.save(test_output_file);

    // Read object code to cpu
    std::ifstream infile(test_output_file, std::ios::binary);
    infile.seekg(0, infile.end);
    int length = infile.tellg();
    infile.seekg(0, infile.beg);
    int num_instrument = length / sizeof(uint32_t);
    char *buffer = new char[4];

    for (int i = 0; i < num_instrument; i++)
    {
        infile.read(buffer, sizeof(uint32_t));
        const uint32_t *output_num = reinterpret_cast<const uint32_t *>(buffer);
        cpu.inst_mem.write(i << 2, *output_num);
    }

    // cpu.run

    L_(ldebug4) << "before process:";

    while (!cpu.is_end_of_program())
    {
        cpu.process();
    }
    L_(ldebug4) << "after process:";

    cpu.data_mem.show();

    REQUIRE(true);
}
//----------------------------------------------------------------------------