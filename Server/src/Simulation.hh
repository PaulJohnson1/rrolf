#pragma once

#include <cstdint>
#include <vector>
#include <functional>

#include <System/Physics.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{

    class Server;
    class Entity;
    class Client;
    class Camera;

    constexpr uint16_t MAX_ENTITY_COUNT = UINT16_MAX;

    class Simulation
    {
        system::Physics m_Physics;

    public:
        Server &m_Server;
        Entity *m_Entities[MAX_ENTITY_COUNT] = {};

        Simulation(Server &);

        void Remove(Entity *);
        void WriteUpdate(bc::BinaryCoder &, Camera &);
        void Tick();
        // use if you want bound checking
        Entity &GetEntity(uint16_t id);
        template <typename T>
        void ForEachEntity(T callback)
        {
            for (uint16_t i = 0; i < MAX_ENTITY_COUNT; i++)
                if (m_Entities[i] != nullptr)
                    callback(*m_Entities[i]);
        }
        std::vector<uint16_t> FindEntitiesInView(Camera &camera);
        Entity &Create();
    };
}
