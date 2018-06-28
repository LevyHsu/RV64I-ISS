#ifndef PROCESSOR_H
#define PROCESSOR_H

/* ****************************************************************
   RISC-V Instruction Set Simulator
   Computer Architecture, Semester 1, 2018

   Class for processor

**************************************************************** */

#include "memory.h"

using namespace std;

class processor {

 private:

  // TODO: Add private members here
  bool debug;
  int *pc_array;
  int **register_array;
  int **csr_array;
  unsigned int Privilege_level;
  bool csr_defined[4096];
  bool f11_f14_read_only;
  long long int instruction_executed;
  memory* Main_Memory;
  uint64_t breakpoint;


 public:

  // Consructor
  processor(memory* main_memory, bool verbose);

  // Display PC value
  void show_pc();

  // Set PC to new value
  void set_pc(uint64_t new_pc);

  uint64_t return_pc();

  uint64_t return_reg(unsigned int reg_num);

  // Display register value
  void show_reg(unsigned int reg_num);

  // Set register to new value
  void set_reg(unsigned int reg_num, uint64_t new_value);

  // Execute a number of instructions
  void execute(unsigned int num, bool breakpoint_check,processor* CPU);

  // Clear breakpoint
  void clear_breakpoint();

  // Set breakpoint at an address
  void set_breakpoint(uint64_t address);

  void set_instruction_count(uint64_t count);

  uint64_t get_instruction_count();

  // Used for Postgraduate assignment. Undergraduate assignment can return 0.
  uint64_t get_cycle_count();

  // Show privilege level
  void show_prv();

  // Set privilege level
  void set_prv(unsigned int prv_num);

  unsigned int return_prv();

  // Display CSR value
  void show_csr(unsigned int csr_num);

  uint64_t return_csr(unsigned int csr_num);

  // Set CSR to new value
  void set_csr(unsigned int csr_num, uint64_t new_value);

  bool csr_is_defined(unsigned int csr_num);

  bool illegal_csr_write(unsigned int csr_num);
};

#endif
