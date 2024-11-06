#include "memory/cpu_memory.h"
#include "instructions.h"
#ifndef CPU_H
#define CPU_H

typedef struct
{
    uint32_t identifier;
    uint32_t address;
} Label;

typedef struct
{
    // Refererar egentligen till registrena men orkar inte byta namn nu
    CPUMemory memory;
    // detta är då det "riktiga" minnet
    uint8_t *ram;
    instruction_t *program;
    uint32_t program_counter;
    // Label sparar alla ställen där en label har placerats
    Label *labels;
    int n_labels;
} CPU;

CPU init_cpu(instruction_t *program);

void execute_instruction(CPU *cpu, instruction_t raw_instruction);
#endif