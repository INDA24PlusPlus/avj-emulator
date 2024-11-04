#include "cpu_memory.h"
#include "register.h"
#include <stdlib.h>

// Initialize everything to zero
CPUMemory initialize_memory()
{
    Register *registers = malloc((sizeof(Register)) * N_REGISTERS);
    for (int i = 0; i < N_REGISTERS; i++)
    {
        if (i == 0)
        {
            Register reg = {.is_constant = 1, .value = 0};
            registers[i] = reg;
        }
        else
        {

            Register reg = {.is_constant = 0, .value = 0};
            registers[i] = reg;
        }
    }

    CPUMemory memory = {.registers = registers};

    return memory;
}

void set_memory(CPUMemory *memory, int register_number, uint32_t value)
{
    if (register_number > 31)
    {
        return;
    }

    store(&(memory->registers[register_number]), value);
}

uint32_t load_memory(CPUMemory *memory, int register_number)
{
    if (register_number > 31)
    {
        exit(-1);
    }

    uint32_t value = ((memory->registers[register_number]).value);
    return value;
}
