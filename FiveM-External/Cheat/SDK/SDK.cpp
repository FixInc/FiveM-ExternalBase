#include "SDK.h"

bool CPed::GetPlayer(uintptr_t& base)
{
    ptr = base;
    return ptr == NULL ? false : true;
}
bool CPed::IsPlayer()
{
    return player_info != NULL;;
}
bool CPed::IsDead()
{
    return m_fHealth <= 0 || m_vPosition == Vector3(0.f, 0.f, 0.f);
}
bool CPed::Update()
{
    player_info = m.Read<uintptr_t>(ptr + offset::playerinfo);
    //weapon_manager = m.Read<uintptr_t>(ptr + offset::WeaponManager);

    m_fHealth = m.Read<float>(ptr + offset::health);
    m_vPosition = m.Read<Vector3>(ptr + offset::position);

    if (IsDead())
        return false;

    m_fArmor = m.Read<float>(ptr + offset::armor);
    m_fMaxHealth = m.Read<float>(ptr + offset::maxhealth);
    m_bMatrix = m.Read<Matrix>(ptr + offset::boneMatrix);

    return true;
}

Vector3 CPed::GetBonePosition(const int& BoneID)
{
    Vector3 bone = m.Read<Vector3>(ptr + 0x410 + (BoneID * 0x10));
    Vector3 transform = Vec3_Transform(&bone, &m_bMatrix);

    return transform;
}

float GetDistance(Vector3 value1, Vector3 value2)
{
    float num = value1.x - value2.x;
    float num2 = value1.y - value2.y;
    float num3 = value1.z - value2.z;

    return sqrt(num * num + num2 * num2 + num3 * num3);
}

bool Vec3_Empty(const Vector3& value)
{
    return value == Vector3(0.f, 0.f, 0.f);
}

Vector3 Vec3_Transform(Vector3* vIn, Matrix* mIn)
{
    Vector3 pOut{};
    pOut.x = vIn->x * mIn->_11 + vIn->y * mIn->_21 + vIn->z * mIn->_31 + 1.f * mIn->_41;
    pOut.y = vIn->x * mIn->_12 + vIn->y * mIn->_22 + vIn->z * mIn->_32 + 1.f * mIn->_42;
    pOut.z = vIn->x * mIn->_13 + vIn->y * mIn->_23 + vIn->z * mIn->_33 + 1.f * mIn->_43;

    return pOut;
};

bool WorldToScreen(Matrix ViewMatrix, Vector3& vWorld, Vector2& vOut)
{
    Matrix v = ViewMatrix.Transpose();
    Vector4 vec = Vector4(v._21, v._22, v._23, v._24), vec_y = Vector4(v._31, v._32, v._33, v._34), vec_z = Vector4(v._41, v._42, v._43, v._44);
    Vector3 vec_out = Vector3((vec.x * vWorld.x) + (vec.y * vWorld.y) + (vec.z * vWorld.z) + vec.w,
        (vec_y.x * vWorld.x) + (vec_y.y * vWorld.y) + (vec_y.z * vWorld.z) + vec_y.w,
        (vec_z.x * vWorld.x) + (vec_z.y * vWorld.y) + (vec_z.z * vWorld.z) + vec_z.w);

    if (vec_out.z <= 0.001f)
        return false;

    vec_out.z = 1.0f / vec_out.z;
    vec_out.x *= vec_out.z;
    vec_out.y *= vec_out.z;

    const float width = (float)g.GameRect.right;
    const float height = (float)g.GameRect.bottom;
    float x_temp = width / 2;
    float y_temp = height / 2;

    vOut.x += x_temp + float(0.5f * vec_out.x * width + 0.5f);
    vOut.y = y_temp - float(0.5f * vec_out.y * height + 0.5f);

    return true;
}