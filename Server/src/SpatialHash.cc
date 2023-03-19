#include <cstdint>
#include <SpatialHash.hh>
#include <Entity/Entity.hh>
#include <vector>
#include <array>

SpatialHash::SpatialHash()
{
    for (int32_t n = 0; n < space; ++n)
    {
        m_Grid.at(n) = std::vector<Entity *>();
    }
}
void SpatialHash::insert(Entity *e)
{
    int32_t sx = ((int32_t)e->m_Position->X() - (int32_t)e->m_Physics->Radius()) >> m_GRID_SIZE;
    int32_t sy = ((int32_t)e->m_Position->Y() - (int32_t)e->m_Physics->Radius()) >> m_GRID_SIZE;
    int32_t ex = ((int32_t)e->m_Position->X() + (int32_t)e->m_Physics->Radius()) >> m_GRID_SIZE;
    int32_t ey = ((int32_t)e->m_Position->Y() + (int32_t)e->m_Physics->Radius()) >> m_GRID_SIZE;
    for (int32_t y = sy; y <= ey; ++y)
    {
        if (y < 0)
            continue;
        for (int32_t x = sx; x <= ex; ++x)
        {
            if (x < 0)
                continue;
            uint32_t hash = x | y << m_HASH_SIZE;
            if (hash >= space)
                continue; // should never happen
            m_Grid.at(hash).push_back(e);
        }
    }
}

std::vector<Entity *> SpatialHash::getCollisions(float x, float y, float w, float h)
{
    std::vector<Entity *> ret = {};
    int32_t sx = ((int32_t)x - (int32_t)w) >> m_GRID_SIZE;
    int32_t sy = ((int32_t)y - (int32_t)h) >> m_GRID_SIZE;
    int32_t ex = ((int32_t)x + (int32_t)w) >> m_GRID_SIZE;
    int32_t ey = ((int32_t)y + (int32_t)h) >> m_GRID_SIZE;
    for (int32_t y = sy; y <= ey; ++y)
    {
        if (y < 0)
            continue;
        for (int32_t x = sx; x <= ex; ++x)
        {
            if (x < 0)
                continue;
            uint32_t hash = x | y << m_HASH_SIZE;
            if (hash >= space)
                continue; // should never happen
            for (Entity *ent : m_Grid.at(hash))
            {
                if (ent->m_QueryId == m_QueryId)
                    continue;
                ent->m_QueryId = m_QueryId;
                ret.push_back(ent);
            }
        }
    }
    m_QueryId++;
    return ret;
}
std::vector<Entity *> SpatialHash::getCollisions(Entity *ent)
{
    return getCollisions(ent->m_Position->X(), ent->m_Position->Y(), ent->m_Physics->Radius(), ent->m_Physics->Radius());
}
void SpatialHash::clear()
{
    for (int32_t n = 0; n < space; ++n)
    {
        m_Grid.at(n).clear();
    }
}
