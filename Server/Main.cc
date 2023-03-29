#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Server.hh>
#include <Server/Simulation.hh>

int main()
{
    using namespace app;

    Server &server = *new Server;

    server.Run();
    return 0;
}
