
typedef enum
{
    ADD,
    ADDI,
    ADDIU,
    ADDU,
    AND,
    // Branch instruction
    BEQ,
    BNE,
    // Jump instructions
    JALR,
    JR,
    J,
    JAL,
    // Load instructions
    LB,
    LBU,
    LUI,
    LW,
    MUL,
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
} Instructions;

enum PseudoInstructions
{
    LOAD_ADDRESS,
    LOAD_ADDRESS_I,
    BRANCH_LESS_OR_EQ,
    NOOP,
    MOVE
};