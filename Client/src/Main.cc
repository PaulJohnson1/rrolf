#include <iostream>
#include <unistd.h>

#include <Simulation.hh>
#include <Socket.hh>
#include <Renderer.hh>

int main()
{
    using namespace app;

    // heap allocate so the dtor doesn't automatically get called
    Socket *socket = new Socket("ws://localhost:8000");
    Simulation *simulation = new Simulation;
#ifdef WASM_BUILD
    Renderer *renderer = new Renderer(*simulation);
    renderer->Initialize();
#else
    std::thread([&]()
                {   Renderer *renderer = new Renderer(*simulation);
                    renderer->Initialize(); })
        .detach();
#endif
    socket->m_OnClose = [&]()
    { std::cout << "close\n"; };
    socket->m_OnOpen = [&]()
    { std::cout << "open\n"; };
    socket->m_OnMessage = [&](uint8_t *a)
    { simulation->ReadBinary(a); };

    socket->Connect();
}
