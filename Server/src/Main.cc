#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server.hh>
#include <Simulation.hh>
#include <Entity/Entity.hh>

int main()
{
    Server server;
    // server.Run();

    Entity &a = server.m_Simulation.Create();
    a.m_Position->X(122);
    a.m_Position->Y(1233);
    a.m_Position->Angle(3.14159265358979 - 2);
    a.m_Physics->Radius(123121212);

    Camera camera;
    static uint8_t data[1024*1024*8];
    bc::BinaryCoder coder{data};
    server.m_Simulation.WriteUpdate(coder, camera);

    std::cout << coder.At() << '\n';

    /*
        00          // deletion count
        01          // update count

        01          // creation type
        00          // entity id
        03          // component flags

        07          // position state
        00 00 f4 42 // position x value
        00 20 9a 44 // position y value
        b5 1f 92 3f // angle

        01          // physics state
        c8 d5 ea 4c // physics radius
    */
    for (uint64_t i = 0; i < coder.At(); i++)
        std::cout << std::hex << (int32_t)coder.Data()[i] << ' ';
    
    std::cout << '\n';

    return 0;
}
