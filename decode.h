#ifndef DECODE_H
#define DECODE_H

//#include <iostream>
#include <string>
#include <inttypes.h>
#include "memory.h"
#include "processor.h"

enum instruction { red, green, blue };

class instructions
{
    private:
    memory* Main_Memory;
    processor* CPU;
    int *instruction_array;
    bool debug;

    public:
    instructions(memory* main_memory,processor* cpu,bool verbose);
    void array_load(uint64_t memory_address);
    string instraction_type();
    long long int return_signed_bit_value(int begin,int end);
    long long int return_unsigned_bit_value(int begin,int end);
    void execute_command(uint64_t memory_address);
};

#endif
//011001011010
//1626+