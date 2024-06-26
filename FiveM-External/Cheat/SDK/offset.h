#pragma once

// b2944
namespace offset
{
    // Base
    constexpr auto GameWorld = 0x257BEA0;
    constexpr auto ReplayInterface = 0x1F42068;
    constexpr auto ViewPort = 0x1FEAAC0;

    // Ped
    constexpr auto m_pBoneMatrix = 0x60;
    constexpr auto m_pLocation = 0x90;
    constexpr auto m_pGodMode = 0x189;
    constexpr auto m_pHealth = 0x280;
    constexpr auto m_pMaxHealth = 0x284;
    constexpr auto m_pArmor = 0x150C;

    // Pointer (CPed->this)
    constexpr auto m_pInfo = 0x10A8;    // PlayerInfo
    constexpr auto m_pWeaponManager = 0x10B8;

    // Ped->WeaponMgr->this
    constexpr auto w_pSpread = 0x74;
    constexpr auto w_pRecoil = 0x2F4;
    constexpr auto w_pRange  = 0x28C;
}

// しかのこのこのここしたんたん

/*  [ 簡単なゲームの構造 ]
    GameWorld -> 0x8 = LocalPlayer

    ReplayInterface -> 0x18 -> 0x100 = PedList

    ViewPort -> 0x24C = ViewMatrix
*/