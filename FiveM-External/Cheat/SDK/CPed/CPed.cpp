#include "CPed.h"

bool CPed::get_player(uintptr_t& base)
{
    ptr = base;
    return ptr == NULL ? false : true;
}

bool CPed::isPlayer()
{
    return player_info != NULL;;
}

bool CPed::isDead()
{
    return m_fHealth <= 0 || m_vPosition == Vector3(0.f, 0.f, 0.f);
}

bool CPed::Update()
{
    player_info = m.Read<uintptr_t>(ptr + offset::m_pInfo);
    uintptr_t weapon_mgr = m.Read<uintptr_t>(ptr + offset::m_pWeaponManager);
    current_weapon = m.Read<uintptr_t>(weapon_mgr + 0x20);

    m_fHealth = m.Read<float>(ptr + offset::m_pHealth);
    m_vPosition = m.Read<Vector3>(ptr + offset::m_pLocation);

    if (isDead())
        return false;

    m_fArmor = m.Read<float>(ptr + offset::m_pArmor);
    m_fMaxHealth = m.Read<float>(ptr + offset::m_pMaxHealth);
    m_bMatrix = m.Read<Matrix>(ptr + offset::m_pBoneMatrix);
    UpdateBones();

    return true;
}

// 1(2)RPMでBoneの読み取りを行う
void CPed::UpdateBones()
{
    CBone bone = m.Read<CBone>(ptr + 0x410); // 0x430
    BoneList[HEAD] = Vec3_Transform(&bone.gHead, &m_bMatrix);
    BoneList[LEFTFOOT] = Vec3_Transform(&bone.gLeftFoot, &m_bMatrix);
    BoneList[RIGHTFOOT] = Vec3_Transform(&bone.gRightFoot, &m_bMatrix);
    BoneList[LEFTANKLE] = Vec3_Transform(&bone.gLeftAnkle, &m_bMatrix);
    BoneList[RIGHTANKLE] = Vec3_Transform(&bone.gRightAnkle, &m_bMatrix);
    BoneList[LEFTHAND] = Vec3_Transform(&bone.gLeftHand, &m_bMatrix);
    BoneList[RIGHTHAND] = Vec3_Transform(&bone.gRightHand, &m_bMatrix);
    BoneList[NECK] = Vec3_Transform(&bone.gNeck, &m_bMatrix);
    BoneList[HIP] = Vec3_Transform(&bone.gHip, &m_bMatrix);
}

/* - D3DXVECTOR, D3DXMATRIXを使うな
Vector3 CPed::GetBonePosition(const int& BoneID)
{
    Vector3 bone = m.Read<Vector3>(ptr + 0x410 + (BoneID * 0x10)); // 0x430
    Vector3 transform = Vec3_Transform(&bone, &m_bMatrix);

    return transform;
}*/