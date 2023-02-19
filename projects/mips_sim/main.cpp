#include <iostream>
#include <iostream>
#include <string>

#include "data_path.h"
#include "mips_sim/simulator/simulator.h"

bool is_help(std::string str)
{
    return (str.compare("-h") == 0 || str.compare("--help") == 0);
}

int main(int argc, char *argv[])
{
    std::string in_file;
    std::string mem_file;

    // Parse inupt.
    switch (argc)
    {
    case 1: // only execute
        std::cout << "Neither input.asm nor in.hex is provided."
                  << "A default sample files are executed. Please see -h / --help."
                  << std::endl
                  << std::endl;

        in_file = std::string(IN_DATA_PATH) + "/simulator/in_loop.asm";
        mem_file = std::string(IN_DATA_PATH) + "/simulator/in_loop.hex";
        break;
    case 2:
        if (is_help(argv[1]))
        {
            std::cout << "usage ./mips_simulate in.asm(must) in.hex(option)"
                      << std::endl
                      << std::endl;
            return 0;
        }
        else
        {
            in_file = argv[1];
            mem_file = "";
        }
        break;
    case 3:
        in_file = argv[1];
        mem_file = argv[2];
        break;
    default:
        std::cout << "error inupt, please see --help or -h" << std::endl;
        return -1;
    }

    Simulator sim;
    sim.simulate(in_file, mem_file);
    sim.show_status();
    return 0;
}