#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Server.hh>
#include <Server/Simulation.hh>

int main()
{
    using namespace app;

    Server &server = *new Server;

    Entity id = server.m_Simulation.Create();
    component::Physical &physical = server.m_Simulation.AddComponent<component::Physical>(id);
    component::Render &render = server.m_Simulation.AddComponent<component::Render>(id);
    physical.X(122);
    physical.Y(123);
    physical.Angle(3.14159265358979 - 2);
    physical.Radius(50.0f);
    physical.m_Velocity.Set(0.0f, 1.0f);
    
    server.Run();
    return 0;
}
