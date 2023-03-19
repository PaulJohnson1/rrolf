#pragma once

#include <cstdint>
#include <vector>
#include <functional>

class Server;
class Entity;
class Client;
class Camera;

namespace bc
{
    class BinaryCoder;
}

constexpr uint16_t MAX_ENTITY_COUNT = UINT16_MAX;

class Simulation
{
public:
    Server &m_Server;
    Entity *m_Entities[MAX_ENTITY_COUNT] = {};

    Simulation(Server &);

    void Remove(Entity *);
    void WriteUpdate(bc::BinaryCoder &, Camera &);
    void Tick();
    // use if you want bound checking
    Entity &GetEntity(uint16_t id);
    // TODO: replace with iterator
    void ForEachEntity(std::function<void(Entity &)>);
    std::vector<uint16_t> FindEntitiesInView(Camera &camera);
    Entity &Create();
};
