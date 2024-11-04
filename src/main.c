#include <stdio.h>
#include <stdint.h>

int main()
{
    uint32_t instruct = 0x014B4820;
    uint8_t op = (instruct >> 0) & 0x1F;
    printf("Hello world: %d", op);

    return 0;
}