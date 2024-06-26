#pragma once
#include "../../../Utils/Memory/Memory.h"
#include "../Game/GameSDK.h"
#include "../offset.h"

class CPed
{
public:
    uintptr_t ptr;
    uintptr_t player_info;
    uintptr_t current_weapon;

    float m_fArmor;
    float m_fHealth;
    float m_fMaxHealth;
    Vector3 m_vPosition;
    Matrix m_bMatrix;
    Vector3 BoneList[9]{};

    bool get_player(uintptr_t& base);
    bool isPlayer();
    bool isDead();
    bool Update();
    void UpdateBones();
    //Vector3 GetBonePosition(const int& BoneID);
};