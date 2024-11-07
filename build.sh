#!/bin/sh

gcc -o emulator src/main.c src/cpu.c src/memory/cpu_memory.c src/memory/register.c src/instructions.c src/examples/sum_n.c -Wall -Wextra -pedantic -std=c99