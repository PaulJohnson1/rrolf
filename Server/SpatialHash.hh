#pragma once

#include <cstdint>
#include <list>
#include <vector>
#include <array>

#include <Shared/Entity.hh>

namespace app
{
    class Simulation;

    class SpatialHash
    {
        uint32_t m_QueryId = 0;
        Simulation &m_Simulation;

    public:
        static constexpr uint32_t GRID_SIZE = 5;
        static constexpr uint32_t HASH_TABLE_SIZE = 65537;
        // std::vector<Entity> *m_Cells = new std::vector<Entity>[HASH_TABLE_SIZE];
        std::vector<Entity> m_Entities;

        SpatialHash(Simulation &);

        void Insert(Entity);
        void Clear();
        std::vector<Entity> GetCollisions(int32_t, int32_t, int32_t, int32_t);
        std::vector<Entity> GetCollisions(Entity);
    };
}
