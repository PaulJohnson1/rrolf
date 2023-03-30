#include <Client/Component/Ai.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    Ai::Ai(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    void Ai::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        coder.Read<bc::VarUint>();
    }
}
