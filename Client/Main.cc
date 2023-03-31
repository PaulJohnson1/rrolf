#include <iostream>
#include <unistd.h>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Socket.hh>
#include <Client/Renderer.hh>
#include <Client/Ui/Text.hh>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

// #include <fenv.h>

int main()
{
    // feenableexcept(FE_INVALID);
    using namespace app;

    // heap allocate so the dtor doesn't automatically get called
    static Simulation *simulation = new Simulation();
    static Renderer *renderer = new Renderer([](void) -> void
    {
        simulation->TickRenderer(renderer);
    });
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
            movementFlags |= (renderer->m_KeysPressed[87] || renderer->m_KeysPressed[38]) << 0;
            movementFlags |= (renderer->m_KeysPressed[65] || renderer->m_KeysPressed[37]) << 1;
            movementFlags |= (renderer->m_KeysPressed[83] || renderer->m_KeysPressed[40]) << 2;
            movementFlags |= (renderer->m_KeysPressed[68] || renderer->m_KeysPressed[39]) << 3;
            coder.Write<bc::Uint8>(movementFlags);
            socket->SendPacket(coder.Data(), coder.At());
        });
#ifdef EMSCRIPTEN
    std::cout << "wasm init\n";
    renderer->Initialize();
#else
    std::thread([&]()
                { renderer->Initialize(); })
        .detach();
#endif

    socket->Connect();
}
