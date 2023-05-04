#include <Client/Component/Heal.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    Heal::Heal(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    void Heal::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        coder.Read<bc::VarUint>();
    }
}
