/* ****************************************************************
   RISC-V Instruction Set Simulator
   Computer Architecture, Semester 1, 2018

   Command interpreter

**************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <ctype.h>

#include "memory.h"
#include "processor.h"
#include "commands.h"

using namespace std;


void command_skip_optional_whitespace(string& command, unsigned int& i) {
  while (i < command.length() && isspace(command[i])) i++;
}


bool command_skip_required_whitespace(string& command, unsigned int& i) {
  if (i == command.length() || !isspace(command[i])) return false;
  i++;
  while (i < command.length() && isspace(command[i])) i++;
  return true;
}


bool command_match_decimal_number(string& command, unsigned int& i, unsigned int& num) {
  unsigned int j = i;
  while (j < command.length() && isdigit(command[j])) j++;
  if (j == i) return false;
  stringstream(command.substr(i, j - i)) >> num;
  i = j;
  return true;
}


bool command_match_hex_number(string& command, unsigned int& i, uint64_t& num) {
  unsigned int j = i;
  while (j < command.length() && isxdigit(command[j])) j++;
  if (j == i) return false;
  stringstream(command.substr(i, j - i)) >> hex >> num;
  i = j;
  return true;
}


bool command_match_blank(string& command, unsigned int i) {
  return i == command.length() || command[i] == '#';
}


bool command_match_x(string& command, unsigned int i, bool& data_present, unsigned int& num, uint64_t& data) {
  data_present = false;
  if (i == command.length() || command[i] != 'x') return false;
  i++;
  if (!command_match_decimal_number(command, i, num)) return false;
  command_skip_optional_whitespace(command, i);
  if (i < command.length() && command[i] == '=') {
    i++;
    data_present = true;
    command_skip_optional_whitespace(command, i);
    if (!command_match_hex_number(command, i, data)) return false;
    command_skip_optional_whitespace(command, i);
  }
  return i == command.length() || command[i] == '#';
}


bool command_match_pc(string& command, unsigned int i, bool& address_present, uint64_t& address) {
  address_present = false;
  if (i == command.length() || command[i] != 'p') return false;
  i++;
  if (i == command.length() || command[i] != 'c') return false;
  i++;
  command_skip_optional_whitespace(command, i);
  if (i < command.length() && command[i] == '=') {
    i++;
    address_present = true;
    command_skip_optional_whitespace(command, i);
    if (!command_match_hex_number(command, i, address)) return false;
    command_skip_optional_whitespace(command, i);
  }
  return i == command.length() || command[i] == '#';
}


bool command_match_m(string& command, unsigned int i, bool& data_present, uint64_t& address, uint64_t& data) {
  data_present = false;
  if (i == command.length() || command[i] != 'm') return false;
  i++;
  if (!command_skip_required_whitespace(command, i)) return false;
  if (!command_match_hex_number(command, i, address)) return false;
  command_skip_optional_whitespace(command, i);
  if (i < command.length() && command[i] == '=') {
    i++;
    data_present = true;
    command_skip_optional_whitespace(command, i);
    if (!command_match_hex_number(command, i, data)) return false;
    command_skip_optional_whitespace(command, i);
  }
  return i == command.length() || command[i] == '#';
}


bool command_match_dot(string& command, unsigned int i, bool& num_present, unsigned int& num) {
  num_present = false;
  if (i == command.length() || command[i] != '.') return false;
  i++;
  if (i == command.length() || command[i] == '#') return true;
  if (!command_skip_required_whitespace(command, i)) return false;
  if (command_match_decimal_number(command, i, num)) {
    num_present = true;
    command_skip_optional_whitespace(command, i);
  }
  return i == command.length() || command[i] == '#';
}


bool command_match_b(string& command, unsigned int i, bool& address_present, uint64_t& address) {
  address_present = false;
  if (i == command.length() || command[i] != 'b') return false;
  i++;
  if (i == command.length() || command[i] == '#') return true;
  if (!command_skip_required_whitespace(command, i)) return false;
  if (command_match_hex_number(command, i, address)) {
    address_present = true;
    command_skip_optional_whitespace(command, i);
  }
  return i == command.length() || command[i] == '#';
}


bool command_match_l(string& command, unsigned int i, string& filename) {
  unsigned int j;
  if (i == command.length() || command[i] != 'l') return false;
  i++;
  if (!command_skip_required_whitespace(command, i)) return false;
  if (i == command.length() || command[i] != '"') return false;
  i++;
  j = i;
  while (j < command.length() && command[j] != '"') j++;
  filename = command.substr(i, j - i);
  i = j;
  if (i == command.length() || command[i] != '"') return false;
  i++;
  command_skip_optional_whitespace(command, i);
  return i == command.length() || command[i] == '#';
}


// Command interpreter function
void interpret_commands(memory* main_memory, processor* cpu, bool verbose) {

  string command;
  unsigned int i;
  bool address_present, data_present, num_present;
  uint64_t address, data;
  unsigned int num;
  string filename;

  while (true) {
    getline(cin, command);  // Read the next line of input
    if (!cin) break;        // Exit if end of input file
    i = 0;
    command_skip_optional_whitespace(command, i);
    if (command_match_blank(command, i)) {  // Check for blank command
      // Nothing to do
    }
    else if (command_match_x(command, i, data_present, num, data)) {  // Check for x command
      if (num > 31) {
	cout << "Incorrect register number" << endl;
      }
      else if (!data_present) {  // No new value
	cpu->show_reg(num);  // so just show register value
      }
      else {
	cpu->set_reg(num, data);  // Update register
      }
    }
    else if (command_match_pc(command, i, address_present, address)) {  // Check for pc command
      if (!address_present) {  // No new value
	cpu->show_pc();  // so just show pc value
      }
      else {
	cpu->set_pc(address);  // Update pc
      }
    }
    else if (command_match_m(command, i, data_present, address, data)) {  // Check for m command
      if (!data_present) {  // No new value
	main_memory->show_address(address);  // so just show memory word value
      }
      else {
	main_memory->set_address(address, data);  // Update memory word
      }
    }
    else if (command_match_dot(command, i, num_present, num)) {  // Check for . command
      if (!num_present) {  // No instruction count value
	cpu->execute(1, false, cpu);  // so just execute one instruction without breakpoint check
      }
      else {
	cpu->execute(num, true, cpu);  // Execute specified number of instructions with breakpoint check
      }
    }
    else if (command_match_b(command, i, address_present, address)) {  // Check for b command
      if (!address_present) {  // No address value
	cpu->clear_breakpoint();  // so just clear breakpoint
      }
      else {
	cpu->set_breakpoint(address);  // Set breakpoint at the address
      }
    }
    else if (command_match_l(command, i, filename)) {  // Check for l command
      uint64_t start_address;
      if (main_memory->load_file(filename, start_address)) {  // Load using the specified file name
	cpu->set_pc(start_address);
      }
    }
    else {
      cout << "Unrecognized command" << endl;
    }
  }
}
