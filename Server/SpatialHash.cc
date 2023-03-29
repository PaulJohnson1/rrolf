#include <Server/SpatialHash.hh>

#include <cstdint>
#include <vector>
#include <array>

#include <Server/Simulation.hh>

namespace app
{
    /*
    4: 10'000
    5: 3'200
    6: 2'000
    7: 1'650
    8: 1'750
    9: 2'300
    10: 2'800
    */
    static constexpr uint32_t GRID_SIZE = 7;

    SpatialHash::SpatialHash(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void SpatialHash::Insert(Entity id)
    {
        // m_Entities.push_back(id);
        component::Physical physical = m_Simulation.Get<component::Physical>(id);
        int32_t entityX = (int32_t)physical.X();
        int32_t entityY = (int32_t)physical.Y();
        int32_t entitySize = (int32_t)physical.Radius();

        int32_t sx = (entityX - entitySize) >> GRID_SIZE;
        int32_t sy = (entityY - entitySize) >> GRID_SIZE;
        int32_t ex = (entityX + entitySize) >> GRID_SIZE;
        int32_t ey = (entityY + entitySize) >> GRID_SIZE;
        for (int32_t y = sy; y <= ey; y++)
        {
            for (int32_t x = sx; x <= ex; x++)
            {
                uint32_t hash = ((x << 16) | (y >> 16)) % HASH_TABLE_SIZE;
                m_Cells[hash].push_back(id);
            }
        }
    }

    std::vector<Entity> SpatialHash::GetCollisions(int32_t x, int32_t y, int32_t w, int32_t h)
    {
        std::vector<Entity> result = {};
        result.reserve(128); // some random number lol
        int32_t sx = (x - w) >> GRID_SIZE;
        int32_t sy = (y - h) >> GRID_SIZE;
        int32_t ex = (x + w) >> GRID_SIZE;
        int32_t ey = (y + h) >> GRID_SIZE;
        for (int32_t y = sy; y <= ey; y++)
            for (int32_t x = sx; x <= ex; x++)
            {
                uint32_t hash = ((x << 16) | (y >> 16)) % HASH_TABLE_SIZE;
                std::vector<Entity> &cell = m_Cells[hash];
                for (uint64_t i = 0; i < cell.size(); i++)
                {
                    component::Physical &physical = m_Simulation.Get<component::Physical>(cell[i]);
                    if (physical.m_QueryId != m_QueryId)
                    {
                        physical.m_QueryId = m_QueryId;
                        result.push_back(cell[i]);
                    }
                }
            }

        m_QueryId++;
        return result;

        // return m_Entities;
    }
    std::vector<Entity> SpatialHash::GetCollisions(Entity id)
    {
        component::Physical &physical = m_Simulation.Get<component::Physical>(id);
        int32_t entityX = (int32_t)physical.X();
        int32_t entityY = (int32_t)physical.Y();
        int32_t entitySize = (int32_t)physical.Radius();

        return GetCollisions(entityX, entityY, entitySize, entitySize);

        // return m_Entities;
    }
    void SpatialHash::Clear()
    {
        for (int32_t i = 0; i < HASH_TABLE_SIZE; i++)
            m_Cells[i].clear();
        // m_Entities.clear();
    }
}
