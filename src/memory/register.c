#include "register.h"
#include <stdint.h>

void store(Register *reg, int32_t value)
{
    reg->value = value;
}

int32_t load(Register *reg)
{
    return reg->value;
}