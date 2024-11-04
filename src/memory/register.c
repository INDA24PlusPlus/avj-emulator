#include "register.h"
#include <stdint.h>

void store(Register *reg, uint32_t value)
{
    reg->value = value;
}

uint32_t load(Register *reg)
{
    return reg->value;
}