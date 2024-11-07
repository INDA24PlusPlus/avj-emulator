#include <stdint.h>
#include "../instructions.h"
#include "../cpu.h"
#include <stdlib.h>
#include <stdio.h>

/*

    # Initialize registers
    lui $t0, 0
    ori $t0, $t0, 5

    addi $t1, $zero, 0
    addi $t2, $zero, 0

    # Main loop body
loop:	addi	$t1, $t1, 1	# i = i + 1
    add	$t2, $t2, $t1	# sum = sum + i
    beq	$t0, $t1, exit	# if i = N, continue
    j	loop
exit:
sll $zero,$zero,0
*/

void run()
{
    instruction_t i0 = 0x3C080000;
    instruction_t i1 = 0x35080005;
    instruction_t i2 = 0x20090000;
    instruction_t i3 = 0x200A0000;

    instruction_t i4 = 0x21290001;
    instruction_t i5 = 0x1495020;
    instruction_t i6 = 0x11090002;
    instruction_t i7 = 0x8000004;
    instruction_t i8 = 0x0;

    instruction_t *program = malloc(sizeof(instruction_t) * 9);
    program[0] = i0;
    program[1] = i1;
    program[2] = i2;
    program[3] = i3;
    program[4] = i4;
    program[5] = i5;
    program[6] = i6;
    program[7] = i7;
    program[8] = i8;

    CPU cpu = init_cpu(program);
    // Eftersom vi bara kör binär kod direkt måste vi göra såna här jobbiga grejer
    cpu.n_labels = 2;
    cpu.program_length = 9;
    Label *labels = malloc(sizeof(Label) * 3);
    // Loop label
    Label l1 = {.identifier = 4, .address = 0x00000010};
    //
    Label l2 = {.identifier = 2, .address = 0x0000001C};
    labels[0] = l1;
    labels[1] = l2;
    cpu.labels = labels;

    run_program(&cpu);
    // After we have run the program
    int32_t result = load_memory(&(&cpu)->memory, 10);
    printf("Result after loops: %d \n", result);
}