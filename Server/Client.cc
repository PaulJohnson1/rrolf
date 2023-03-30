#include <Server/Client.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Server.hh>
#include <Server/Simulation.hh>

namespace app
{
    Client::Client(websocketpp::connection_hdl hdl, Simulation &simulation)
        : m_Hdl(hdl),
          m_Simulation(simulation)
    {
        std::cout << "client create\n";
        m_PlayerInfo = m_Simulation.Create();
        component::PlayerInfo &playerInfo = m_Simulation.AddComponent<component::PlayerInfo>(m_PlayerInfo);
        playerInfo.Player(m_Simulation.Create());
        playerInfo.HasPlayer(true);
        component::Flower &flower = m_Simulation.AddComponent<component::Flower>(playerInfo.Player());
        component::Basic &basic = m_Simulation.AddComponent<component::Basic>(playerInfo.Player());
        component::Life &life = m_Simulation.AddComponent<component::Life>(playerInfo.Player());
        component::Physical &physical = m_Simulation.AddComponent<component::Physical>(playerInfo.Player());
        physical.Radius(25.0f);
        physical.m_Restitution = 0.1;
        life.m_Damage = 10;
        life.MaxHealth(1000);
        life.Health(900); // a test
        basic.Team(0);
    }

    Client::~Client()
    {
        std::cout << "client destroy\n";

        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_PlayerInfo);

        if (playerInfo.HasPlayer())
            m_Simulation.Remove(playerInfo.Player());
        m_Simulation.Remove(m_PlayerInfo);
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

    void Client::SendPacket(bc::BinaryCoder const &data) const
    {
        std::string packet{data.Data(), data.Data() + data.At()};

        m_Simulation.m_Server.m_Server.send(m_Hdl, packet, websocketpp::frame::opcode::binary);
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
            if (size != 3)
            {
                std::cout << "someone sent update packet with size not equal to 3\n";
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

            m_PlayerAcceleration.Set(x, y);
            m_PlayerAcceleration.Normalize();
        }
    }

    websocketpp::connection_hdl Client::GetHdl() { return m_Hdl; }
}
