#include <Client/Component/Ai.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    Projectile::Projectile(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    void Projectile::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        coder.Read<bc::VarUint>();
    }
}
