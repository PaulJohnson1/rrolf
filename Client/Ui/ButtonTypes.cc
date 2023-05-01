#include <Client/Ui/ButtonTypes.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <cstdint>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Client/Socket.hh>
#include <Client/Ui/Container.hh>
#include <Client/Ui/LabeledButton.hh>
#include <Client/Ui/DynamicButton.hh>

namespace app::ui
{
    LabeledButton *CreateRespawnButton(Renderer *renderer)
    {
        LabeledButton *button = new LabeledButton(*renderer, 100, 40, "Continue", 20);
        button->m_R = 6;
        button->m_Fill = 0xff1dd129;
        button->m_Stroke = 0xff17a921;
        button->m_LineWidth = 6;
        button->m_OnMouseOver = [&]() {
        };
        button->m_OnMouseMove = [&]() {
        };
        button->m_OnMouseDown = [&]() {
        };
        button->m_OnMouseUp = [&]()
        {
            static uint8_t outgoingInputPacket[60];
            bc::BinaryCoder coder{outgoingInputPacket};
            coder.Write<bc::Uint8>(1);
            g_Simulation->m_Socket->SendPacket(coder.Data(), coder.At());
        };
        return button;
    }
    
    DynamicButton *CreateLoadoutButton(Renderer *renderer, int32_t pos)
    {
        DynamicButton *button = new DynamicButton(*renderer, 60, pos);
        button->m_Fill = 0xffffffff;
        button->m_Stroke = 0xffcfcfcf;
        button->m_OnMouseOver = [&]() {
        };
        button->m_OnMouseMove = [button]()
        {
            button->m_GlobalX = g_InputData->m_MouseX;
            button->m_GlobalY = g_InputData->m_MouseY;
        };
        button->m_OnMouseDown = [button]()
        {
            button->m_UseGlobalPosition = true;
            button->m_GlobalX = g_InputData->m_MouseX;
            button->m_GlobalY = g_InputData->m_MouseY;
        };
        button->m_OnMouseUp = [button]()
        {
            button->m_UseGlobalPosition = false;
        };
        return button;
    }
    DynamicButton *CreateSecondaryButton(Renderer *renderer, int32_t pos)
    {
        DynamicButton *button = new DynamicButton(*renderer, 40, pos);
        button->m_Fill = 0xffffffff;
        button->m_Stroke = 0xffcfcfcf;
        button->m_OnMouseOver = [&]() {
        };
        button->m_OnMouseMove = [button]()
        {
            button->m_GlobalX = g_InputData->m_MouseX;
            button->m_GlobalY = g_InputData->m_MouseY;
        };
        button->m_OnMouseDown = [button]()
        {
            button->m_UseGlobalPosition = true;
            button->m_GlobalX = g_InputData->m_MouseX;
            button->m_GlobalY = g_InputData->m_MouseY;
        };
        button->m_OnMouseUp = [button]()
        {
            button->m_UseGlobalPosition = false;
        };
        return button;
    }
}