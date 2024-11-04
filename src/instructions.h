#include <stdint.h>
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
typedef enum
{
    ADD,
    ADDI,
    ADDIU,
    ADDU,
    AND,
    ANDI,
    // Branch instruction
    BEQ,
    BNE,
    // Jump instructions
    JALR,
    JR,
    JUMP,
    JAL,
    // Load instructions
    LB,
    LBU,
    LUI,
    LW,
    MUL,
    MULU,
    NOR,
    OR,
    ORI,
    // Set instructions
    SLT,
    SLTU,
    SLTI,
    SLTIU,
    // SHift instructions
    SLL,
    SLLV,
    SRA,
    SRL,
    SRLV,
    SB,
    SW,
    SUB,
    SUBU,
    XOR,
    XORI
} InstructionType;

typedef enum
{
    R,
    I,
    J
} InstructionFormat;

typedef struct
{
    InstructionType type;
    InstructionFormat format;
} Instruction;

typedef uint32_t instruction_t;

enum PseudoInstructions
{
    LOAD_ADDRESS,
    LOAD_ADDRESS_I,
    BRANCH_LESS_OR_EQ,
    NOOP,
    MOVE
};

Instruction match_op_code(instruction_t raw_instruction);

#endif