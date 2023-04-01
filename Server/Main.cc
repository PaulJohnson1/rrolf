#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Server.hh>
#include <Server/Simulation.hh>

#include <fenv.h>

int main()
{
    feenableexcept(FE_INVALID);
    using namespace app;

    Server &server = *new Server;

    server.Run();
    return 0;
}
