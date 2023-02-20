# MIPS Sim

## Motivation


While learning [Computer Organizatino [1]](https://www.google.com/books/edition/_/2-izngEACAAJ?sa=X&ved=2ahUKEwiep9asqaL9AhXEiFwKHcKiDeoQre8FegQILRAa), it seemed like I know every block's behaviour but I was still confused sometimes about how they all connected with each other and actually works perfectly.

At this moment, practice is essential to solidify and verify the understanding of theory. I developed a simple CPU simulator and corresponding assembler in this repository to verify my implementation. After this, I can finally confirm my understanding of CPU.

## Features
- C++11 implementation based on the bible [[1]](https://www.google.com/books/edition/_/2-izngEACAAJ?sa=X&ved=2ahUKEwiep9asqaL9AhXEiFwKHcKiDeoQre8FegQILRAa).
    - Simplified function for easier understanding.
- Self-explanatory code (I hope).
    - Single responsibility principle. Each block has its class, and each function has only one responsibility.
    - Unit test framework to show the usage of each essential block, because I'm a fan of TDD procedure.
- Classic sample
    - A loop counting the lump sum of adding from 1 to 10 is provided. This example utilizes all the instructions taught in Chapter 4.4.
- Debug Interface
    - Users can set the initial condition of data memory; this facilitates the learning process and simplify the machine code.
    - Simulator.show() outputs the memory data and register files.
    - Configurable logging.
        - By setting the Logger level in CMakeLists.txt, users can show input/output signals per block in the CPU.
- Little dependency and easy to execute.
    - Test Data and relative path have been set.


## Functions
- Assembler/Parser (Ch. 2)
- Single cycle CPU design (Ch. 4.4)
### Comming soon
- Pipeline CPU (Ch. 4.5-4.8)

## Usage
- Biuld:
~~~shell
user$mkdir build

user$cd build

user$../configure

user$make -j8 # 8 threads
~~~
- Execution (--help):
~~~shell
user$./mips_simulate --help

usage ./mips_simulate in.asm(must) in.hex(option)
~~~
- Execution (default loop sample):
~~~shell
user$./mips_simulate

Neither input.asm nor in.hex is provided.A default sample files are executed. Please see -h / --help.

INFO, simulator.cpp, show_status: start of reg.show():
INFO, register_file.cpp, show: $s0: a
INFO, register_file.cpp, show: $s1: 1
INFO, register_file.cpp, show: $s2: a
INFO, register_file.cpp, show: $s3: 37
INFO, simulator.cpp, show_status: start of data_mem.show():
INFO, memory_unit.cpp, show: address: 0, value: 1
INFO, memory_unit.cpp, show: address: 4, value: a
INFO, memory_unit.cpp, show: address: 8, value: 37
INFO, simulator.cpp, show_status: end of show()
~~~

## Unit test
- Introduction:
    - It's highly recommended to learn via unit test.
    - Testing data and relative path have already set.
- Build:
~~~shell
user$mkdir build
user$cd build
user$../configure -ut # the only difference
user$make -j8
~~~
- Execution:
~~~shell
user$./mips_ut.

INFO, simulator.cpp, show_status: start of reg.show():
...
INFO, simulator.cpp, show_status: start of data_mem.show():
...
INFO, simulator.cpp, show_status: end of show()

==========================================================
All tests passed (15 assertions in 12 test cases)

~~~


## Folder Organization
- include/mips_sim:
    - Assembler
        - Assemble files to simplified objective files.
    - CUP
        - All components in CPU.
    - Simulator:
        - Wraper of assmbler and cpu.
- projects:
    - mips_sim: example usage of Simulator.
    - unit_test: files for TDD

## Dependency
- OS: linux
- Unit test: catch2

## Reference
[1] [Computer Organizatino and Design MIPS Edition 5th, David A. Patterson/John L. Hennessy](https://www.google.com/books/edition/_/2-izngEACAAJ?sa=X&ved=2ahUKEwiep9asqaL9AhXEiFwKHcKiDeoQre8FegQILRAa)