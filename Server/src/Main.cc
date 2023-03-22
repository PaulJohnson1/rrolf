#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server.hh>
#include <Simulation.hh>

int main()
{
    using namespace app;

    Server server;

    Entity id = server.m_Simulation.Create();
    component::Position &position = server.m_Simulation.AddComponent<component::Position>(id);
    component::Physics &physics = server.m_Simulation.AddComponent<component::Physics>(id);
    position.X(122);
    position.Y(123);
    position.Angle(3.14159265358979 - 2);
    physics.Radius(50.0f);
    physics.m_Velocity.Set(0.0f, 1.0f);
    
    server.Run();

    // Camera camera;

    // static uint8_t data[1024*1024*8];
    // bc::BinaryCoder coder{data};
    // server.m_Simulation.WriteUpdate(coder, camera);

    // for (uint64_t i = 0; i < coder.At(); i++)
    //     std::cout << std::hex << (int32_t)coder.Data()[i] << ' ';
    // std::cout << '\n';
    // server.m_Simulation.Tick();
    // coder.At(0);
    // server.m_Simulation.WriteUpdate(coder, camera);
    // for (uint64_t i = 0; i < coder.At(); i++)
    //     std::cout << std::hex << (int32_t)coder.Data()[i] << ' ';
    // std::cout << '\n';
    // a.m_Position->Angle(3.14159265358979 - 2);
    // a.m_Position->X(123);
    // coder.At(0);
    // server.m_Simulation.WriteUpdate(coder, camera);
    // for (uint64_t i = 0; i < coder.At(); i++)
    //     std::cout << std::hex << (int32_t)coder.Data()[i] << ' ';
    // std::cout << '\n';

    return 0;
}
