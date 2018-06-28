/* ****************************************************************
   RISC-V Instruction Set Simulator
   Computer Architecture, Semester 1, 2018

   Main program

**************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

#include "memory.h"
#include "processor.h"
#include "commands.h"
#include <inttypes.h> // unit64_t temporary for my IDE

using namespace std;

int main(int argc, char* argv[]) {

    // Values of command line options. 
    string arg;
    bool verbose = false;
    bool cycle_reporting = false;

    memory* main_memory;
    processor* cpu;
    
    //DEBUG FIELD
    /*
    main_memory = new memory (verbose);
    cpu = new processor (main_memory, verbose);
    
    main_memory->write_doubleword(0xF52ABC6666666666ULL,0xFF0000000000061DULL,0xFFFFFFFFFFFFFFFFULL);
    main_memory->write_doubleword(0x0EC000300AC00080ULL,0xF30000000000061DULL,0xFFFFFFFFFFFFFFFFULL);
    main_memory->show_address(0xF52ABC6666666666ULL);
    main_memory->show_address(0x0EC000300AC00080ULL);
    cpu->test(0xF52ABC6666666666ULL);
    cpu->test(0x0EC000300AC00080ULL);
    */
    
    unsigned long int cpu_instruction_count;

    for (int i = 1; i < argc; i++) {
	// Process the next option
	arg = string(argv[i]);
	if (arg == "-v")  // Verbose output
	    verbose = true;
	else if (arg == "-c")  // Cycle and instruction reporting enabled
	    cycle_reporting = true;
	else {
	    cout << "Unknown option: " << arg << endl;
	}
    }

    main_memory = new memory (verbose);
    cpu = new processor (main_memory, verbose);

    interpret_commands(main_memory, cpu, verbose);
    
    // Report final statistics

    cpu_instruction_count = cpu->get_instruction_count();
    cout << "Instructions executed: " << dec << cpu_instruction_count << endl;
    
    if (cycle_reporting) {
	// Required for postgraduate Computer Architecture course
	unsigned long int cpu_cycle_count;

	cpu_cycle_count = cpu->get_cycle_count();

	cout << "CPU cycle count: " << dec << cpu_cycle_count << endl;
    }
    
}
