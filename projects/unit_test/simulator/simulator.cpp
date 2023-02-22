#include <catch2/catch.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "unit_test/data_path.h"
#include "mips_sim/simulator/simulator.h"

//----------------------------------------------------------------------------
TEST_CASE("classic operation Pipeline", "[simulator]")
{
    Simulator sim;
    std::string in_file = std::string(IN_DATA_PATH) + "/simulator/in.asm";
    std::string mem_file = std::string(IN_DATA_PATH) + "/simulator/init.hex";
    sim.simulate(in_file, mem_file);
    sim.show_status();
}
//----------------------------------------------------------------------------
TEST_CASE("loop operation Pipeline", "[simulator]")
{
    Simulator sim;
    std::string in_file = std::string(IN_DATA_PATH) + "/simulator/in_loop.asm";
    std::string mem_file = std::string(IN_DATA_PATH) + "/simulator/in_loop.hex";
    sim.simulate(in_file, mem_file);
    sim.show_status();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
TEST_CASE("classic operation Single Cycle", "[simulator]")
{
    Simulator sim("SingleCycle");
    std::string in_file = std::string(IN_DATA_PATH) + "/simulator/in.asm";
    std::string mem_file = std::string(IN_DATA_PATH) + "/simulator/init.hex";
    sim.simulate(in_file, mem_file);
    sim.show_status();
}
//----------------------------------------------------------------------------
TEST_CASE("loop operation Single Cycle", "[simulator]")
{
    Simulator sim("SingleCycle");
    std::string in_file = std::string(IN_DATA_PATH) + "/simulator/in_loop.asm";
    std::string mem_file = std::string(IN_DATA_PATH) + "/simulator/in_loop.hex";
    sim.simulate(in_file, mem_file);
    sim.show_status();
}
//----------------------------------------------------------------------------