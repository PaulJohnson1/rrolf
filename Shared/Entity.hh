#pragma once

#include <cstdint>

#define FOR_EACH_COMPONENT                \
    RROLF_COMPONENT_ENTRY(Flower, 0)      \
    RROLF_COMPONENT_ENTRY(Petal, 1)       \
    RROLF_COMPONENT_ENTRY(Ai, 2)          \
    RROLF_COMPONENT_ENTRY(ArenaInfo, 3)   \
    RROLF_COMPONENT_ENTRY(Life, 4)        \
    RROLF_COMPONENT_ENTRY(Physical, 5)    \
    RROLF_COMPONENT_ENTRY(Mob, 6)         \
    RROLF_COMPONENT_ENTRY(PlayerInfo, 7)  \
    RROLF_COMPONENT_ENTRY(Basic, 8)       \
    RROLF_COMPONENT_ENTRY(Drop, 9)        \
    RROLF_COMPONENT_ENTRY(Projectile, 10) \
    RROLF_COMPONENT_ENTRY(Heal, 11)

namespace app
{
    using Entity = uint16_t;
    constexpr Entity MAX_ENTITY_COUNT = 768;
}
