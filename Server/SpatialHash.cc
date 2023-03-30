#include <Server/SpatialHash.hh>

#include <cstdint>
#include <vector>
#include <array>

#include <Server/Simulation.hh>

namespace app
{
    /*
    1: 1
    2: 0.72
    3: 0.41
    4: 0.40
    5: 0.33
    6: 0.42
    */
    static constexpr uint32_t GRID_SIZE = 5;
    static constexpr uint32_t HASH_TABLE_SIZE = 2048;

    SpatialHash::SpatialHash(Simulation &simulation)
        : m_Simulation(simulation),
          m_Cells(new std::vector<Entity>[HASH_TABLE_SIZE])
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
                uint64_t hash = (uint64_t(x) * 89533 + uint64_t(y)) % HASH_TABLE_SIZE;
                m_Cells[hash].push_back(id);
            }
        }
    }

    std::vector<Entity> SpatialHash::GetCollisions(int32_t _x, int32_t _y, int32_t _w, int32_t _h)
    {
        std::vector<Entity> result = {};
        int32_t sx = (_x - _w) >> GRID_SIZE;
        int32_t sy = (_y - _h) >> GRID_SIZE;
        int32_t ex = (_x + _w) >> GRID_SIZE;
        int32_t ey = (_y + _h) >> GRID_SIZE;
        for (int32_t y = sy; y <= ey; y++)
            for (int32_t x = sx; x <= ex; x++)
            {
                uint64_t hash = (uint64_t(x) * 89533 + uint64_t(y)) % HASH_TABLE_SIZE;
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