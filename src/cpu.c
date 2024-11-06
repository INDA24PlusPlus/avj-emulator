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

void find_label(Label *label, CPU *cpu, uint32_t label_identifier)
{

    for (int i = 0; i < cpu->n_labels; i++)
    {
        if (cpu->labels[i].identifier == label_identifier)
        {
            label = &(cpu->labels[i]);
        }
    }
}

int32_t sign_extended(int16_t value)
{
    return (int32_t)value;
}

int32_t sign_extended_u8(uint8_t value)
{
    return (int32_t)value;
}

uint32_t zero_extension(uint8_t value)
{
    return (uint32_t)value;
}

uint32_t zero_extension_u16(uint16_t value)
{
    return (uint32_t)value;
}

CPU init_cpu(instruction_t *program)
{
    CPUMemory memory = initialize_memory();
    uint8_t ram = malloc(sizeof(uint8_t) * 4096);
    CPU cpu = {
        .memory = memory,
        .ram = ram,
        .program = program,
        .program_counter = 0};
    return cpu;
}

void run_program(CPU *cpu)
{
    int program_length = sizeof(instruction_t) / cpu->program[0];

    while (cpu->program_counter != program_length)
    {
        execute_instruction(cpu, cpu->program[cpu->program_counter]);
    }
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
            // 31 refers to $ra register
            set_memory(&cpu->memory, 31, cpu->program_counter + 4);
            cpu->program_counter = rs_value;
        }
        case JR:
        {
            cpu->program_counter = rs_value;
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

        int16_t immediate = raw_instruction & ((1U << 16) - 1);
        int32_t rs_value = load_memory(&cpu->memory, rs);
        int32_t rt_value = load_memory(&cpu->memory, rs);

        switch (parsed_instruction.type)
        {
        case ADDI:
        {
            if (addition_overflow(rs_value, immediate) == 1)
            {
                printf("ERROR: Addition overflow for registers %d and %d", rs, rt);
                exit(-1);
            };
            int32_t sum = rs_value + sign_extended(immediate);
            set_memory(&cpu->memory, rt, sum);
        }
        case ADDIU:
        {
            int32_t sum = rs_value + sign_extended(immediate);
            set_memory(&cpu->memory, rt, sum);
        }
        case ANDI:
        {
            int32_t result = rs_value & sign_extended(immediate);
            set_memory(&cpu->memory, rt, result);
        }
        case BEQ:
        {
            if (rs_value == rt_value)
            {
                uint32_t bta = cpu->program_counter + 4 + (sign_extended(immediate) * 4);
                cpu->program_counter = bta;
            }
        }
        case BNE:
        {
            if (rs_value != rt_value)
            {
                uint32_t bta = cpu->program_counter + 4 + (sign_extended(immediate) * 4);
                cpu->program_counter = bta;
            }
        }
        case LB:
        {
            int address = rs_value + sign_extended(immediate);
            uint8_t value = cpu->ram[address];

            set_memory(&cpu->memory, rt, sign_extended_u8(value));
        }
        case LBU:
        {
            int address = rs_value + sign_extended(immediate);
            uint8_t value = cpu->ram[address];

            set_memory(&cpu->memory, rt, zero_extension(value));
        }
        case LUI:
        {
            int16_t zeroes = 0;
            int32_t result = (immediate << 16) | zeroes;

            set_memory(&cpu->memory, rt, result);
        }
        case LW:
        {
            int address = rs_value + sign_extended(immediate);
            uint8_t value = cpu->ram[address];

            set_memory(&cpu->memory, rt, value);
        }
        case ORI:
        {
            int32_t value = rs_value | zero_extension_u16(immediate);

            set_memory(&cpu->memory, rt, value);
        }
        case SLTI:
        {
            if (rs_value < sign_extended(immediate))
            {
                set_memory(&cpu->memory, rt, 1);
            }
            else
            {

                set_memory(&cpu->memory, rt, 0);
            }
        }
        case SLTIU:
        {
            if (rs_value < sign_extended(immediate))
            {
                set_memory(&cpu->memory, rt, 1);
            }
            else
            {
                set_memory(&cpu->memory, rt, 0);
            }
        }

        case SB:
        {
            int address = rs_value + sign_extended(immediate);
            cpu->ram[address] = rt_value;
        }
        case SW:
        {
            int address = rs_value + sign_extended(immediate);
            cpu->ram[address] = rt_value;
        }

        default:
            break;
        }
    }
    else if (parsed_instruction.format == J)
    {
        uint32_t address = raw_instruction & ((1U << 26) - 1);

        switch (parsed_instruction.type)
        {
        case JUMP:
        {
            // JTA = concat((PC + 4), address(label), 00)
            // PC = JTA
            uint32_t pc_bits = (cpu->program_counter >> 28) & 0xF;
            Label l = {};
            find_label(&l, cpu, address);
            uint32_t jta = (pc_bits << 28) | (l.address << 2);
            cpu->program_counter = jta;
        }
        case JAL:
        {
            uint32_t pc_bits = (cpu->program_counter >> 28) & 0xF;
            Label l = {};
            find_label(&l, cpu, address);
            uint32_t jta = (pc_bits << 28) | (l.address << 2);
            cpu->program_counter = jta;
            set_memory(&cpu->memory, 31, cpu->program_counter + 4);
        }

        default:
            break;
        }
    }
}
