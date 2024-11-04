#include <register.h>
typedef struct
{
    // registers
    Register *registers;
} CPUMemory;

#define N_REGISTERS 32