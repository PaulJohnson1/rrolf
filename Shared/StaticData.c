#include <Shared/StaticData.h>

struct rr_petal_data PETAL_DATA[max_petals];

void rr_set_petal_data(uint32_t id, float health, float damage, uint32_t cooldown)
{
    PETAL_DATA[id].id = id;
    PETAL_DATA[id].health = health;
    PETAL_DATA[id].damage = damage;
    PETAL_DATA[id].cooldown = cooldown;
}
