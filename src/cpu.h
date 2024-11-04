#include "memory/cpu_memory.h"
#include "instructions.h"
#ifndef CPU_H
#define CPU_H

typedef struct
{
    CPUMemory memory;
} CPU;

CPU init_cpu();

void execute_instruction(CPU *cpu, instruction_t raw_instruction);
#endif