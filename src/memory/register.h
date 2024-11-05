#include <stdint.h>
#ifndef REGISTER_H
#define REGISTER_H
typedef struct
{
    int32_t value;
    int is_constant;
} Register;

int32_t load(Register *reg);
void store(Register *reg, int32_t value);

#define REGISTER_SIZE 32;

#endif