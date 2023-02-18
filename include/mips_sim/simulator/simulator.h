#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <string>
#include <vector>

#include "mips_sim/cpu/cpu_single_cycle.h"
#include "mips_sim/assembler/assembler.h"

class Simulator
{
public:
    Simulator() = default;
    void simulate(std::string asm_file, std::string mem = "");
    void show_status();

private:
    Assembler assembler;
    CPU_SingleCycle cpu;
};

#endif // __SIMULATOR_H__