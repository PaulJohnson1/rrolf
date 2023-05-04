#include <Server/Component/Heal.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Component/Petal.hh>
#include <Server/Simulation.hh>

namespace app::component
{
    Heal::Heal(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Heal::~Heal()
    {
    }

    void Heal::Reset()
    {
    }

    void Heal::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        coder.Write<bc::VarUint>(0);
    }
}