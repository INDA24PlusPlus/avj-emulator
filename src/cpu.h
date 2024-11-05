#include "memory/cpu_memory.h"
#include "instructions.h"
#ifndef CPU_H
#define CPU_H

typedef struct
{
    // Refererar egentligen till registrena men orkar inte byta namn nu
    CPUMemory memory;
    uint8_t *ram;
} CPU;

CPU init_cpu();

void execute_instruction(CPU *cpu, instruction_t raw_instruction);
#endif