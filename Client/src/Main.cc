#include <iostream>
#include <unistd.h>

#include <Socket.hh>

int main()
{
    using namespace app;
    std::cout << "it works\n";

    // heap allocate so the dtor doesn't automatically get called
    Socket *socket = new Socket("ws://localhost:8000");
    socket->m_OnClose = [&]()
    { std::cout << "close\n"; };
    socket->m_OnOpen = [&]()
    { std::cout << "open\n"; };
    socket->m_OnMessage = [&](uint8_t *a)
    {
        std::cout << "message " << (void *)a << '\n';
    };

    socket->Connect();
}
