#pragma once

#include <vector>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;
}

namespace app::component
{
    class PlayerInfo
    {
        bool m_HasPlayer;
        Entity m_Player = (Entity)-1;
        float m_Fov = 0.9f;
        float m_CameraX = 0.0f;
        float m_CameraY = 0.0f;
        Simulation *m_Simulation;

    public:
        using Type = PlayerInfo;

        Entity m_Parent;
        uint64_t m_State = 0;

        std::vector<Entity> m_EntitiesInView;

        PlayerInfo(Entity, Simulation *);
        ~PlayerInfo();

        float Fov() const;
        float CameraX() const;
        float CameraY() const;
        bool HasPlayer() const;
        Entity Player() const;
        void Fov(float);
        void CameraX(float);
        void CameraY(float);
        void HasPlayer(bool);
        void Player(Entity);

        void Reset();

        static void Write(bc::BinaryCoder &, Type, bool isCreation);
    };
}