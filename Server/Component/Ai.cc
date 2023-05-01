#include <Server/Component/Ai.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    Ai::Ai(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Ai::~Ai()
    {
    }

    void Ai::Reset()
    {
    }

    void Ai::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        coder.Write<bc::VarUint>(0);
    }
}
