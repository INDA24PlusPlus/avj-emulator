#include <stdint.h>
#include "register.h"
#ifndef CPU_MEMORY_H
#define CPU_MEMORY_H
typedef struct
{
    // registers
    Register *registers;
} CPUMemory;

void set_memory(CPUMemory *memory, int register_number, int32_t value);
uint32_t load_memory(CPUMemory *memory, int register_number);
CPUMemory initialize_memory();

#define N_REGISTERS 32
#endif