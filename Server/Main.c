#include <Server/Simulation.h>

#include <stdio.h>

void hex_log(uint8_t *arr, uintptr_t len) // with the shadamans power
{
    uintptr_t end = (uintptr_t)arr + len;
    while ((uintptr_t)arr != end)
        printf("%02X ", *(arr++));
    puts("");
}

int main()
{
    struct rr_simulation simulation;
    rr_simulation_init(&simulation);

    EntityIdx i = rr_simulation_alloc_entity(&simulation);
    rr_simulation_add_physical(&simulation, i);
    struct rr_component_physical *physical = rr_simulation_get_physical(&simulation, i);

    static uint8_t data[1000];

    struct rr_encoder c;
    c.data = data;
    c.at = 0;

    puts("a");
    rr_simulation_write_binary(&simulation, &c);
    hex_log(c.data, c.at);
    rr_simulation_free_entity(&simulation, i);
    puts("b");
    rr_simulation_write_binary(&simulation, &c);
    puts("c");
    return 0;
}