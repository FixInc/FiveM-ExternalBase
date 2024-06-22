#pragma once
#include "../../Utils/Memory/Memory.h"
#include "../../Utils/SimpleMath/SimpleMath.h"
#include "../../Utils/Config/Config.h"
#include "../SDK/SDK.h"
using namespace DirectX::SimpleMath;

// b2944
namespace offset
{
    constexpr auto GameWorld = 0x257BEA0;
    constexpr auto ReplayInterface = 0x1F42068;
    constexpr auto ViewPort = 0x1FEAAC0;

    // Ped
    constexpr auto boneMatrix = 0x60;
    constexpr auto position = 0x90;
    constexpr auto health = 0x280;
    constexpr auto maxhealth = 0x284;
    constexpr auto velocity = 0x300;
    constexpr auto playerinfo = 0x10A8;
    constexpr auto armor = 0x150C;

    constexpr auto fGodMode = 0x189;

    // Weapon
    constexpr auto WeaponManager = 0x10D8;
}

class CPed
{
public:
    uintptr_t ptr;
    uintptr_t player_info;

    uintptr_t weapon_manager;

    float m_fArmor;
    float m_fHealth;
    float m_fMaxHealth;
    Vector3 m_vPosition;
    Vector3 m_vVelocity;

    Matrix m_bMatrix;

    bool GetPlayer(uintptr_t& base);
    bool IsPlayer();
    bool IsDead();
    bool Update();
    Vector3 GetBonePosition(const int& BoneID);
};

extern bool Vec3_Empty(const Vector3& value);
extern Vector3 Vec3_Transform(Vector3* vIn, Matrix* mIn);
extern float GetDistance(Vector3 value1, Vector3 value2);
extern bool WorldToScreen(Matrix ViewMatrix, Vector3& vWorld, Vector2& vOut);