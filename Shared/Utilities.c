#include <Shared/Utilities.h>

void rr_log_hex(uint8_t *start, uint8_t *end)
{
    while (start != end)
        printf("%02X ", *start++);
    puts("");
}