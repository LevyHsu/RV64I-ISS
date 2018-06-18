#ifndef MEMORY_H
#define MEMORY_H
#define BLOCKSIZE 1024

#include <vector>
#include <inttypes.h>
/* ****************************************************************
   RISC-V Instruction Set Simulator
   Computer Architecture, Semester 1, 2018

   Class for memory

**************************************************************** */

using namespace std;

class memory {

 private:

    // TODO: Add private members here
  vector<unsigned long long int> block_vector;
  vector<unsigned long long int*> block_pointer;
  bool debug;

 public:
  
  // Constructor
  memory(bool verbose);

  void creat_memory_block(uint64_t address);

  // Read a doubleword of data from a doubleword-aligned address
  uint64_t read_doubleword (uint64_t address);

  uint64_t read_unaligned (uint64_t address);
  // Write a doubleword of data to a doubleword-aligned address,
  // mask contains 1s for bytes to be updated
  void write_doubleword (uint64_t address, uint64_t data, uint64_t mask);

  // Display the doubleword of data at an address
  void show_address (uint64_t address);

  // Set the doubleword of data at an address
  void set_address (uint64_t address, uint64_t data);

  // Load a hex image file
  bool load_file(string file_name, uint64_t &start_address);

};

#endif
