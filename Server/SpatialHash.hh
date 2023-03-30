#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

#include <Shared/Entity.hh>

namespace app
{
    class Simulation;

    class SpatialHash
    {
        uint32_t m_QueryId = 0;
        Simulation &m_Simulation;


    public:
        std::vector<Entity> *m_Cells;
        // std::vector<Entity> m_Entities;

        SpatialHash(Simulation &);

        void Insert(Entity);
        void Clear();
        [[nodiscard]] std::vector<Entity> GetCollisions(int32_t, int32_t, int32_t, int32_t);
        [[nodiscard]] std::vector<Entity> GetCollisions(Entity);
    };
}
