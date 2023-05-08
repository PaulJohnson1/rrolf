#include <Server/Client.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Server.hh>
#include <Server/Simulation.hh>

namespace app
{
    Client::Client(lws *socket, Simulation &simulation)
        : m_Socket(socket),
          m_Simulation(simulation)
    {
        std::cout << "client create\n";
        m_PlayerInfo = m_Simulation.Create();
        m_Simulation.AddComponent<component::PlayerInfo>(m_PlayerInfo);
    }

    Client::~Client()
    {
        std::cout << "client destroy   " << this << ' ' << &m_Simulation << '\n';

        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo);

        if (playerInfo.HasPlayer())
            m_Simulation.RequestDeletion<false>(playerInfo.Player());
        m_Simulation.RequestDeletion<false>(m_PlayerInfo);
    }

    void Client::ConstructPlayer()
    {
        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo);
        if (playerInfo.HasPlayer())
        {
            std::cout << "tried to construct flower but it already exists\n";
            return;
        }
        playerInfo.Player(m_Simulation.Create());
        playerInfo.HasPlayer(true);
        component::Flower &flower = m_Simulation.AddComponent<component::Flower>(playerInfo.Player());
        component::Basic &basic = m_Simulation.AddComponent<component::Basic>(playerInfo.Player());
        component::Life &life = m_Simulation.AddComponent<component::Life>(playerInfo.Player());
        component::Physical &physical = m_Simulation.AddComponent<component::Physical>(playerInfo.Player());
        physical.Radius(25.0f);
        physical.m_Restitution = 1;
        basic.m_Owner = m_PlayerInfo;
        life.m_Damage = 10;
        life.MaxHealth(1000);
        life.Health(life.MaxHealth());
        basic.Team(0);
    }

    void Client::BroadcastUpdate()
    {
        static uint8_t data[1024 * 1024];
        bc::BinaryCoder coder{data};
        coder.Write<bc::Uint8>(0);

        m_Simulation.WriteUpdate(coder, m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo));

        SendPacket(coder);
    }

    void Client::Tick()
    {
        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo);
        if (playerInfo.HasPlayer())
        {
            m_Simulation.Get<component::Physical>(playerInfo.Player()).m_Acceleration = m_PlayerAcceleration;
            if (!playerInfo.HasPlayer())
                return;
            component::Physical &physical = m_Simulation.Get<component::Physical>(playerInfo.Player());
            playerInfo.CameraX(physical.X());
            playerInfo.CameraY(physical.Y());
            if (m_PlayerAcceleration > 0)
                m_Simulation.Get<component::Flower>(playerInfo.Player()).EyeAngle(m_PlayerAcceleration.Theta());
        }

        BroadcastUpdate();
    }

    void Client::SendPacket(bc::BinaryCoder data) const
    {
        // std::unique_lock<std::mutex> l(m_Simulation.m_Server.m_Mutex);
        // try
        // {
        //     auto c = m_Hdl.lock();
        //     if (c)
        //         m_Simulation.m_Server.m_Server.send(c, (void *)data.Data(), data.At(), websocketpp::frame::opcode::binary);
        //     else 
        //         std::cout << "\n\n\nsegmentation fault avoided\n\n\n";
        // }
        // catch (...)
        // {
        //     std::cerr << "SendPacket error\n";
        // }
        // l.unlock();
    }

    void Client::ReadPacket(uint8_t *data, size_t size)
    {
        if (size < 1)
        {
            std::cout << "someone sent packet with size < 1\n";
            return;
        }
        bc::BinaryCoder coder{data};
        uint8_t type = coder.Read<bc::Uint8>();
        if (type == 0)
        {
            if (size < 3)
            {
                std::cout << "someone sent update packet with size less than 3\n";
                return;
            }

            bool mouseMovement = coder.Read<bc::Uint8>();

            if (mouseMovement)
            {
                std::cout << "mouse movement doesn't exist yet\n";
                return;
            }

            uint8_t movementFlags = coder.Read<bc::Uint8>();

            float x = 0;
            float y = 0;

            if (movementFlags & 1)
                y--;
            if (movementFlags & 2)
                x--;
            if (movementFlags & 4)
                y++;
            if (movementFlags & 8)
                x++;

            m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo).m_MouseButton = (movementFlags >> 4) & 7;
            m_PlayerAcceleration.Set(x, y);
            m_PlayerAcceleration.Normalize();
        }
        else if (type == 1)
        {
            ConstructPlayer();
        }
        else if (type == 2)
        {
            if (size != 2)
            {
                std::cout << "someone sent a petal switch packet with size != 3\n";
                return;
            }
            //THIS PROGRAM CREATES BUGS: DO NOT RUN UNLESS YOU FIX THESE BUGS
            //REMEMBER TO DELETE PETALS
            component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo);
            uint32_t pos = coder.Read<bc::Uint8>();
            component::PlayerInfo::PetalSlot &slot = playerInfo.m_PetalSlots[pos];
            uint32_t id1 = slot.m_Data->m_Id; //not a reference
            uint32_t rar1 = slot.m_Rarity; //not a reference
            uint32_t id2 = playerInfo.m_SecondarySlots[pos].m_Data->m_Id; //not a reference
            uint32_t rar2 = playerInfo.m_SecondarySlots[pos].m_Rarity; //not a reference
            for (uint64_t i = 0; i < slot.m_Petals.size(); ++i)
            {
                component::PlayerInfo::Petal &petal = slot.m_Petals[i];
                if (petal.m_IsDead)
                    continue;
                m_Simulation.Get<component::Petal>(petal.m_SimulationId).m_Detached = true;
                m_Simulation.RequestDeletion<true>(petal.m_SimulationId);
            }

            playerInfo.m_PetalSlots[pos] = component::PlayerInfo::MakePetal(id2, rar2);
            playerInfo.m_SecondarySlots[pos] = component::PlayerInfo::MakePetal(id1, rar1);
        }
    }
}
