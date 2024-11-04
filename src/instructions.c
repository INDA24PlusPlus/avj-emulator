#include "instructions.h"

Instruction match_op_code(instruction_t raw_instruction)
{
    // look at first 6 bits to determine op type
    uint8_t op = (raw_instruction >> 26) & 0x3F;

    // Special
    if (op == 0)
    {

        // special instruction, need to look at func_t
        // last 6 bits
        uint8_t func_t = (raw_instruction >> 6) & 0x3F;

        switch (func_t)
        {
        case 32:
        {
            Instruction parsed_instruction = {.type = ADD, .format = R};
            return parsed_instruction;
            break;
        }

        case 33:
        {
            Instruction parsed_instruction = {.type = ADDU, .format = R};
            return parsed_instruction;
            break;
        }
        case 34:
        {
            Instruction parsed_instruction = {.type = SUB, .format = R};
            return parsed_instruction;
            break;
        }
        case 35:
        {
            Instruction parsed_instruction = {.type = SUBU, .format = R};
            return parsed_instruction;
            break;
        }
                case 36:
        {
            Instruction parsed_instruction = {.type = AND, .format = R};
            return parsed_instruction;
            break;
        }
        case 37:
        {
            Instruction parsed_instruction = {.type = OR, .format = R};
            return parsed_instruction;
            break;
        }
        case 38:
        {
            Instruction parsed_instruction = {.type = XOR, .format = R};
            return parsed_instruction;
            break;
        }
        case 39:
        {
            Instruction parsed_instruction = {.type = NOR, .format = R};
            return parsed_instruction;
            break;
        }
        case 0:
        {
            Instruction parsed_instruction = {.type = SLL, .format = R};
            return parsed_instruction;
            break;
        }
        case 2:
        {
            Instruction parsed_instruction = {.type = SRL, .format = R};
            return parsed_instruction;
            break;
        }
        case 3:
        {
            Instruction parsed_instruction = {.type = SRA, .format = R};
            return parsed_instruction;
            break;
        }
        case 4:
        {
            Instruction parsed_instruction = {.type = SLLV, .format = R};
            return parsed_instruction;
            break;
        }
        case 6:
        {
            Instruction parsed_instruction = {.type = SRLV, .format = R};
            return parsed_instruction;
            break;
        }
        case 8:
        {
            Instruction parsed_instruction = {.type = JR, .format = J};
            return parsed_instruction;
            break;
        }
        case 9:
        {
            Instruction parsed_instruction = {.type = JALR, .format = J};
            return parsed_instruction;
            break;
        }
        case 24:
        {
            Instruction parsed_instruction = {.type = MUL, .format = R};
            return parsed_instruction;
            break;
        }
        case 25:
        {
            Instruction parsed_instruction = {.type = MULU, .format = R};
            return parsed_instruction;
            break;
        }
        default:
            break;
        }
    }
    // Immediate
    else
    {
        switch (op)
        {
        case 2:
        {
            Instruction parsed_instruction = {.type = JUMP, .format = J};
            return parsed_instruction;
            break;
        }
        case 3:
        {
            Instruction parsed_instruction = {.type = JAL, .format = J};
            return parsed_instruction;
            break;
        }
        case 4:{
            Instruction parsed_instruction = {.type = BEQ, .format = I};
            return parsed_instruction;
            break;
        }
        case 5:
        {
            Instruction parsed_instruction = {.type = BNE, .format = I};
            return parsed_instruction;
            break;
        }
        case 8:
        {
            Instruction parsed_instruction = {.type = ADDI, .format = I};
            return parsed_instruction;
            break;
        }
        case 9:
        {
            Instruction parsed_instruction = {.type = ADDIU, .format = I};
            return parsed_instruction;
            break;
        }
        case 10:
        {
            Instruction parsed_instruction = {.type = SLTI, .format = I};
            return parsed_instruction;
            break;
        }
        case 11:
        {
            Instruction parsed_instruction = {.type = SLTIU, .format = I};
            return parsed_instruction;
            break;
        }
        case 12:
        {
            Instruction parsed_instruction = {.type = ANDI, .format = I};
            return parsed_instruction;
            break;
        }
        case 13:
        {
            Instruction parsed_instruction = {.type = ORI, .format = I};
            return parsed_instruction;
            break;
        }
        case 14:
        {
            Instruction parsed_instruction = {.type = XORI, .format = I};
            return parsed_instruction;
            break;
        }
        case 15:
        {
            Instruction parsed_instruction = {.type = LUI, .format = I};
            return parsed_instruction;
            break;
        }
        case 32:
        {
            Instruction parsed_instruction = {.type = LB, .format = I};
            return parsed_instruction;
            break;
        }
        case 35:
        {
            Instruction parsed_instruction = {.type = LW, .format = I};
            return parsed_instruction;
            break;
        }
        case 36:
        {
            Instruction parsed_instruction = {.type = LBU, .format = I};
            return parsed_instruction;
            break;
        }
        case 40:
        {
            Instruction parsed_instruction = {.type = SB, .format = I};
            return parsed_instruction;
            break;
        }
        case 43:
        {
            Instruction parsed_instruction = {.type = SW, .format = I};
            return parsed_instruction;
            break;
        }
        default:
            break;
        }
    }
}
