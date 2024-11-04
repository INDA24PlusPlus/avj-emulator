#include "cpu.h"
#include "memory/cpu_memory.h"
#include "instructions.h"
#include "memory/register.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int addition_overflow(uint32_t a, uint32_t b)
{
    if (UINT32_MAX - a < b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

CPU init_cpu()
{
    CPUMemory memory = initialize_memory();
    CPU cpu = {.memory = memory};
    return cpu;
}

void execute_instruction(CPU *cpu, instruction_t raw_instruction)
{
    Instruction parsed_instruction = match_op_code(raw_instruction);

    if (parsed_instruction.format == R)
    {
        uint8_t rs = (raw_instruction >> 21) & 0x1F;
        uint8_t rt = (raw_instruction >> 16) & 0x1F;
        uint8_t rd = (raw_instruction >> 11) & 0x1F;
        // Shift amount
        uint8_t shamt = (raw_instruction >> 6) & 0x1F;

        uint32_t rs_value = load_memory(&cpu->memory, rs);
        uint32_t rt_value = load_memory(&cpu->memory, rt);

        switch (parsed_instruction.type)
        {
        case ADD:
        {
            if (addition_overflow(rs_value, rt_value))
            {
                printf("ERROR: Addition overflow for registers %d and %d", rs, rt);
                exit(-1);
            };
            uint32_t sum = rs_value + rt_value;
            set_memory(&cpu->memory, rd, sum);
            break;
        }
        case ADDU:
        {
            uint32_t sum = rs_value + rt_value;
            set_memory(&cpu->memory, rd, sum);
        }
        default:
            break;
        }
    }
    else if (parsed_instruction.format == I)
    {
        uint8_t rs = (raw_instruction >> 21) & 0x1F;
        uint8_t rt = (raw_instruction >> 16) & 0x1F;
        uint16_t immediate = raw_instruction & ((1U << 16) - 1);
    }
    else if (parsed_instruction.format == J)
    {
        uint32_t address = raw_instruction & ((1U << 26) - 1);
    }
}
