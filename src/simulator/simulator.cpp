#include <fstream>
#include <sstream>
#include "mips_sim/simulator/simulator.h"

//----------------------------------------------------------------------------
bool check_line(std::string line)
{
    std::istringstream ss_cnt(line);
    int cnt = 0;
    std::string tmp;
    while (ss_cnt >> tmp)
    {
        cnt++;
    }
    return cnt == 2;
}
//----------------------------------------------------------------------------
void Simulator::simulate(std::string asm_file, std::string mem_file)
{
    // Assembler
    assembler.load(asm_file);
    std::list<uint32_t> obj_code = assembler.get_obj_code();

    // Transfer object code to cpu's instruction memory
    int address = 0;
    while (!obj_code.empty())
    {
        cpu->inst_mem.write(address, obj_code.front());
        obj_code.pop_front();
        address += 4;
    }

    // Transfer *.hex to cpu's data memory
    if (mem_file.compare("") != 0)
    {
        std::ifstream infile(mem_file);
        if (!infile.is_open())
            L_(lerror) << "memfile is not open, with file name: " << mem_file;

        std::string line;
        while (std::getline(infile, line))
        {
            if (!check_line(line))
            {
                L_(lerror) << "memory .hex format error" << std::endl;
            }
            std::istringstream ss(line);
            std::string word;
            uint32_t value, addr;
            std::vector<uint32_t> pair;
            while (ss >> word)
            {
                std::stringstream ss_hex;
                ss_hex << std::hex << word;
                ss_hex >> value;
                pair.push_back(value);
            }
            L_(ldebug4) << "addr:" << pair[0] << ",value:" << pair[1];
            cpu->data_mem.write(pair[0], pair[1]);
        }
    }

    // Execute cpu
    while (!cpu->is_end_of_program())
    {
        cpu->process();
    }
}
//----------------------------------------------------------------------------
void Simulator::show_status()
{
    L_(linfo) << "start of reg.show():";
    cpu->reg_file.show();
    L_(linfo) << "start of data_mem.show():";
    cpu->data_mem.show();
    L_(linfo) << "end of show()" << std::endl;
}
//----------------------------------------------------------------------------