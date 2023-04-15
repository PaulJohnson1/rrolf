#include <Client/Component/Basic.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    Basic::Basic(Entity parent, Simulation *simulation)
        : m_Parent(parent)
        , m_Simulation(simulation)
        , m_CreationTime(simulation->GetTime())
    {
    }

    void Basic::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Team = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Flags = coder.Read<bc::VarUint>();
    }
}
