#include <Server/Simulation.h>

#include <stdio.h>

void log_hex(uint8_t *start, uint8_t *end)
{
    while (start != end)
        printf("%02X ", *start++);
    puts("");
}

int main()
{
    struct rr_simulation simulation;
    rr_simulation_init(&simulation);

    rr_simulation_alloc_entity(&simulation);

    // testing
    rr_simulation_alloc_entity(&simulation);
    rr_simulation_alloc_entity(&simulation);
    EntityIdx i = rr_simulation_alloc_entity(&simulation);
    rr_simulation_alloc_entity(&simulation);

    rr_simulation_add_physical(&simulation, i);
    struct rr_component_physical *physical = rr_simulation_get_physical(&simulation, i);

    rr_component_physical_set_radius(physical, 10000000.0f);

    static uint8_t data[1000];

    struct rr_encoder c;
    rr_encoder_init(&c, data);    

    puts("a");
    rr_simulation_write_binary(&simulation, &c);
    log_hex(c.start, c.current);
    // restart lol
    c.current = c.start;
    rr_simulation_free_entity(&simulation, i);
    puts("b");
    rr_simulation_write_binary(&simulation, &c);
    puts("c");
    return 0;
}