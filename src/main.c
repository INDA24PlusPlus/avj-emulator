#include <stdio.h>
#include <stdint.h>
#include "cpu.h"

int main()
{
    CPU cpu = init_cpu();

    set_memory(&cpu.memory, 10, 1);
    set_memory(&cpu.memory, 11, 1);

    printf("Before add: %d \n", load_memory(&cpu.memory, 9));
    uint32_t instruct = 0x014B4820;
    execute_instruction(&cpu, instruct);

    printf("After add: %d \n", load_memory(&cpu.memory, 9));
    uint8_t op = (instruct >> 0) & 0x1F;
    printf("Hello world: %d", op);

    return 0;
}