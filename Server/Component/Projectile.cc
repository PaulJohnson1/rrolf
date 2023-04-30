#include <Server/Component/Petal.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    Projectile::Projectile(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }


    void Projectile::Reset()
    {
        m_State = 0;
    }

    void Projectile::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        coder.Write<bc::VarUint>(0);
    }
}
