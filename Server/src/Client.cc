#include <Client.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Simulation.hh>

Client::Client(websocketpp::connection_hdl hdl, Simulation &simulation)
    : m_Hdl(hdl),
      m_Simulation(simulation)
{
    std::cout << "client create\n";
}

Client::~Client()
{
    std::cout << "client destroy\n";
}

void Client::BroadcastUpdate()
{
    static uint8_t data[1024*1024*8];
    //keep it at 8mb then
    bc::BinaryCoder coder{data};
    coder.Write<bc::Uint8>(0);
    m_Simulation.WriteUpdate(coder, m_Camera);
}

void Client::Tick()
{
    BroadcastUpdate();
}

websocketpp::connection_hdl Client::GetHdl()
{
    return m_Hdl;
}
