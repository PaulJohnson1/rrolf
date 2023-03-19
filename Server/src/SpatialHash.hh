#pragma once
#include <cstdint>
#include <list>
#include <vector>
#include <array>

class Entity;
class SpatialHash
{
    uint32_t m_QueryId = 0;

public:
    static uint32_t constexpr m_GRID_SIZE = 5; // 32 x 32
    static uint32_t constexpr m_HASH_SIZE = 5;
    static uint32_t constexpr space = 1 << (m_HASH_SIZE << 1);
    std::array<std::vector<Entity *>, space> m_Grid = {};
    SpatialHash();
    void insert(Entity *);
    void clear();
    std::vector<Entity *> getCollisions(float, float, float, float);
    std::vector<Entity *> getCollisions(Entity *);
};