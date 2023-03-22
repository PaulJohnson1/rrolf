#include <iostream>
#include <unistd.h>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Simulation.hh>
#include <Socket.hh>
#include <Renderer.hh>

#ifdef WASM_BUILD
#include <emscripten.h>
#endif

int main()
{
    using namespace app;

    // heap allocate so the dtor doesn't automatically get called
    static Simulation *simulation = new Simulation();
    static Renderer *renderer = new Renderer(*simulation);
    static Socket *socket = new Socket(
        "ws://localhost:8000", [&]()
        { std::cout << "open\n"; },
        [&]()
        { std::cout << "close\n"; },
        [&](uint8_t *m)
        {
            simulation->ReadBinary(m);
            static uint8_t outgoingInputPacket[20];
            bc::BinaryCoder coder{outgoingInputPacket};
            coder.Write<bc::Uint8>(0);
            coder.Write<bc::Uint8>(0); // keyboard movement
            uint8_t movementFlags = 0;
            movementFlags |= (renderer->m_KeysPressed[82] || renderer->m_KeysPressed[38]) << 0;
            movementFlags |= (renderer->m_KeysPressed[65] || renderer->m_KeysPressed[37]) << 1;
            movementFlags |= (renderer->m_KeysPressed[83] || renderer->m_KeysPressed[40]) << 2;
            movementFlags |= (renderer->m_KeysPressed[87] || renderer->m_KeysPressed[39]) << 3;
            coder.Write<bc::Uint8>(movementFlags);
            socket->SendPacket(coder.Data(), coder.At());
        });
#ifdef WASM_BUILD
    renderer->Initialize();
#else
    std::thread([&]()
                { renderer->Initialize(); })
        .detach();
#endif

    socket->Connect();
}
