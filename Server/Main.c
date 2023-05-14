#include <stdio.h>

#include <Server/Server.h>
#include <Shared/Utilities.h>

void log_hex(uint8_t *start, uint8_t *end)
{
    while (start != end)
        printf("%02X ", *start++);
    puts("");
}

int main()
{
    struct rr_server s;
    rr_server_init(&s);
    rr_server_run(&s);

}