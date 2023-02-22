#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <string>
#include <vector>

#include "mips_sim/cpu/cpu_pipeline.h"
#include "mips_sim/cpu/cpu_single_cycle.h"
#include "mips_sim/assembler/assembler.h"

class Simulator
{
public:
    Simulator(std::string type = "Pipeline")
    {
        if (type.compare("SingleCycle") == 0)
        {
            cpu = std::make_shared<CPU_SingleCycle>();
        }
        else
        {
            cpu = std::make_shared<CPU_Pipeline>();
        }
    };
    void simulate(std::string asm_file, std::string mem = "");
    void show_status();

private:
    Assembler assembler;
    std::shared_ptr<CPU> cpu;
};

#endif // __SIMULATOR_H__