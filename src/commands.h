#ifndef COMMANDS_H
#define COMMANDS_H

#include "memory.h"
#include "processor.h"

void interpret_commands(memory* main_memory, processor* cpu, bool verbose);

#endif
