#pragma once

namespace app
{
    constexpr uint32_t MOB_RARITY_COUNT = 6;

    static constexpr float MOB_SCALE_FACTOR[MOB_RARITY_COUNT] = {
        1,
        1.1,
        1.3,
        1.6,
        3.0,
        5.0
    };

    static constexpr float MOB_HEALTH_FACTOR[MOB_RARITY_COUNT] = {
        1,
        1.6,
        2.5,
        4.0,
        25.0,
        50.0,
    };

    static constexpr float MOB_DAMAGE_FACTOR[MOB_RARITY_COUNT] = {
        1,
        1.1,
        1.3,
        1.6,
        2.0,
        2.5
    };
}
