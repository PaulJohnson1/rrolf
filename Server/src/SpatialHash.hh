#pragma once

#include <cstdint>
#include <list>
#include <vector>
#include <array>

#include <Entity.hh>

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
        std::vector<Entity> *m_Cells = new std::vector<Entity>[HASH_TABLE_SIZE];

        SpatialHash(Simulation &);

        void Insert(uint16_t);
        void Clear();
        std::vector<uint16_t> GetCollisions(int32_t, int32_t, int32_t, int32_t);
        std::vector<uint16_t> GetCollisions(uint16_t);
    };
}
