#include "Cheat.h"

void Cheat::Misc()
{
    while (g.Run)
    {
        // GodMode
        if (g.GodMode && m.Read<bool>(local.ptr + offset::m_pGodMode) == false)
            m.Write<bool>(local.ptr + offset::m_pGodMode, true);
        else if (!g.GodMode && m.Read<bool>(local.ptr + offset::m_pGodMode) == true)
            m.Write<bool>(local.ptr + offset::m_pGodMode, false);

        if (g.NoRecoil)
            m.Write<float>(local.current_weapon + offset::w_pRecoil, 0.f);

        if (g.NoSpread)
            m.Write<float>(local.current_weapon + offset::w_pSpread, 0.f);

        if (g.RangeBypass)
            m.Write<float>(local.current_weapon + offset::w_pRange, 999.f);

        Sleep(100);
    }
}

void Cheat::UpdateList()
{
    while (g.Run)
    {
        std::vector<CPed> list;
        world = m.Read<uintptr_t>(m.BaseAddress + offset::GameWorld);
        local.ptr = m.Read<uintptr_t>(world + 0x8);
        viewport = m.Read<uintptr_t>(m.BaseAddress + offset::ViewPort);

        // Access EntityList
        uintptr_t ReplayInterface = m.Read<uintptr_t>(m.BaseAddress + offset::ReplayInterface);
        uintptr_t EntityListPtr = m.Read<uintptr_t>(ReplayInterface + 0x18);
        uintptr_t EntityList = m.Read<uintptr_t>(EntityListPtr + 0x100);

        for (int i = 0; i < 256; i++)
        {
            CPed ped = CPed{};
            uintptr_t player = m.Read<uintptr_t>(EntityList + (i * 0x10));
            
            if (player == local.ptr)
                continue;
            else if (!ped.get_player(player))
                continue;
            else if (!ped.Update())
                continue;

            list.push_back(ped);
        }

        this->EntityList = list;
        Sleep(500);
    }
}

void Cheat::KeyBinder(int &target_key)
{
    target_key = NULL;

    while (!target_key)
    {
        for (int i = 0; i < 0x87; i++)
        {
            if (i == VK_LWIN || i == VK_RWIN)
                continue;

            if (IsKeyDown(i))
            {
                target_key = i == VK_ESCAPE ? NULL : i;
                break;
            }
        }
    }

    // Check
    if (g.AimKey0 == g.AimKey1)
        g.AimKey1 = 0;

    g.KeyBinding = false;
    g.BindingID = 0;
}