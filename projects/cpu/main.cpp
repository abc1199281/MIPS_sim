#include <string>
#include "mips_sim/simulator/simulator.h"

int main()
{
    Simulator sim;
    std::string asm_file = "test.asm";
    std::string mem_file = "test.hex";
    sim.simulate(asm_file, mem_file);
    sim.show_status();
}