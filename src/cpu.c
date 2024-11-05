#include "cpu.h"
#include "memory/cpu_memory.h"
#include "instructions.h"
#include "memory/register.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int addition_overflow(int32_t a, int32_t b)
{
    if (INT32_MAX - a < b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int multiplication_overflow(int32_t a, int32_t b)
{
    if (INT32_MAX / a < b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int subtraction_overflow(int32_t a, int32_t b)
{
    if (INT32_MAX + a < b)
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

        int32_t rs_value = load_memory(&cpu->memory, rs);
        int32_t rt_value = load_memory(&cpu->memory, rt);

        switch (parsed_instruction.type)
        {
        case ADD:
        {
            if (addition_overflow(rs_value, rt_value) == 1)
            {
                printf("ERROR: Addition overflow for registers %d and %d", rs, rt);
                exit(-1);
            };
            int32_t sum = rs_value + rt_value;
            set_memory(&cpu->memory, rd, sum);
            break;
        }
        case ADDU:
        {
            int32_t sum = rs_value + rt_value;
            set_memory(&cpu->memory, rd, sum);
        }
        case AND:
        {
            int32_t result = rs_value & rt_value;
            set_memory(&cpu->memory, rd, result);
        }
        case JALR:
        {
        }
        case JR:
        {
        }
        case MUL:
        {
            if (multiplication_overflow(rs_value, rt_value))
            {
                printf("ERROR: Multiplication overflow for registers %d and %d", rs, rt);
                exit(-1);
            }
            int32_t product = rs_value * rt_value;
            set_memory(&cpu->memory, rd, product);
        }
        case NOR:
        {
            int32_t result = !(rt_value | rs_value);
            set_memory(&cpu->memory, rd, result);
        }
        case OR:
        {
            int32_t result = (rt_value | rs_value);
            set_memory(&cpu->memory, rd, result);
        }
        case SLT:
        {
            if (rs_value < rt_value)
            {
                set_memory(&cpu->memory, rd, 1);
            }
            else
            {
                set_memory(&cpu->memory, rd, 0);
            }
        }

        case SLTU:
        {
            if (rs_value < rt_value)
            {
                set_memory(&cpu->memory, rd, 1);
            }
            else
            {
                set_memory(&cpu->memory, rd, 0);
            }
        }
        case SLL:
        {
            int32_t result = rt_value << shamt;
            set_memory(&cpu->memory, rd, result);
        }
        case SLLV:
        {
            int32_t result = rt_value << rs_value;
            set_memory(&cpu->memory, rd, result);
        }
        case SRA:
        {
            // borde göra unsigned right shift men finns endast vanlig right shift
            int32_t result = rt_value >> shamt;
            set_memory(&cpu->memory, rd, result);
        }
        case SRL:
        {
            int32_t result = rt_value >> shamt;
            set_memory(&cpu->memory, rd, result);
        }
        case SRLV:
        {
            int32_t result = rt_value >> rs_value;
            set_memory(&cpu->memory, rd, result);
        }
        case SUB:
        {
            if (subtraction_overflow(rs_value, rt_value) == 1)
            {
                printf("ERROR: Addition overflow for registers %d and %d", rs, rt);
                exit(-1);
            }
            int32_t result = rs_value - rt_value;
            set_memory(&cpu->memory, rd, result);
        }
        case SUBU:
        {
            int32_t result = rs_value - rt_value;
            set_memory(&cpu->memory, rd, result);
        }
        case XOR:
        {
            int32_t result = rs_value ^ rt_value;
            set_memory(&cpu->memory, rd, result);
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
