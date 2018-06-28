#ifndef DECODE_H
#define DECODE_H

//#include <iostream>
#include <string>
#include <inttypes.h>
#include "memory.h"
#include "processor.h"


class instructions
{
    private:
    memory* Main_Memory;
    processor* CPU;
    int *instruction_array;
    bool debug;
    void array_load(uint64_t memory_address);
    string instraction_type();
    long long int return_signed_bit_value(int begin,int end);
    long long int return_unsigned_bit_value(int begin,int end);
    void misaligned_load(uint64_t error_address);
    void misaligned_store(uint64_t error_address);
    void machine_mode_interrupt();
    void machine_mode_interrupt_vectored(int causecode);
    void user_mode_interrupt(int mode);
    

    public:
    instructions(memory* main_memory,processor* cpu,bool verbose);  
    void execute_command(uint64_t memory_address);
    void mret(uint64_t memory_address, unsigned int Cause_code);
    void misaligned_instr();
    
};

#endif
//011001011010
//1626+