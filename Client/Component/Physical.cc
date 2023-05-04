#include <Client/Component/Physical.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    Physical::Physical(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
        m_Radius = 1.0f;
    }

    void Physical::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Radius = coder.Read<bc::Float32>();
        if (updatedFields & 2)
            m_X = coder.Read<bc::Float32>();
        if (updatedFields & 4)
            m_Y = coder.Read<bc::Float32>();
        if (updatedFields & 8)
            m_Angle = coder.Read<bc::Float32>();
        if (updatedFields & 16)
            m_DeletionTick = (float) coder.Read<bc::VarUint>();
    }
}
