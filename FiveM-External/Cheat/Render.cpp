#include "Cheat.h"
#include "..\Overlay\Overlay.h"

std::vector<std::string> MenuFCList = { "AimBot", "Visual", "Misc" };

void Cheat::RenderInfo()
{
    // ウォーターマーク的な？
    std::string text = "FiveM | " + std::to_string((int)ImGui::GetIO().Framerate) + "FPS";
    String(ImVec2(8.f, 8.f), ImColor(1.f, 1.f, 1.f, 1.f), text.c_str());

    // クロスヘア
    ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 3, ImColor(0.f, 0.f, 0.f, 1.f));
    ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 2, ImColor(1.f, 1.f, 1.f, 1.f));
}

void Cheat::RenderMenu()
{
    static int Index = 0;

    ImGui::SetNextWindowBgAlpha(0.975f);
    ImGui::SetNextWindowSize(ImVec2(600.f, 450.f));
    ImGui::Begin("FiveM [ EXTERNAL ]", &g.ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // SelectButton
    for (int i = 0; i < MenuFCList.size(); i++)
    {
        static float width = (ImGui::GetContentRegionAvail().x / 3.f) - 6.f;
        if (ImGui::Button(MenuFCList[i].c_str(), ImVec2(width, 35.f)))
            Index = i;

        if (i != MenuFCList.size() - 1)
            ImGui::SameLine();
    }

    ImGui::Spacing();

    //---// Left //--------------------------------------//
    ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 16.f, ImGui::GetContentRegionAvail().y), false);

    switch (Index)
    {
    case 0: // aim
        /* [+] KeyBinder Example
        if (ImGui::Button(g.KeyBinding && g.BindingID == 1 ? "< Press Any Key >" : KeyNames[g.AimKey0], ImVec2(215.f, 20.f)))
        {
            g.KeyBinding = true;
            g.BindingID = 1;
            std::thread([&]() {this->KeyBinder(g.AimKey0); }).detach();
        }
        */
        break;
    case 1: // visual
        ImGui::Text("Visual");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("ESP", &g.ESP);

        ImGui::NewLine();
        ImGui::Spacing();

        ImGui::Text("ESP Options");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Box", &g.ESP_Box);
        ImGui::Checkbox("Line", &g.ESP_Line);
        ImGui::Checkbox("Skeleton", &g.ESP_Skeleton);
        ImGui::Checkbox("Distance", &g.ESP_Distance);
        ImGui::Checkbox("HealthBar", &g.ESP_HealthBar);
        break;
    case 2: // misc
        ImGui::Text("Player");
        ImGui::Separator();
        ImGui::Checkbox("GodMode", &g.GodMode);

        ImGui::NewLine();
        ImGui::Text("Weapon");
        ImGui::Separator();
        ImGui::Checkbox("NoRecoil", &g.NoRecoil);
        ImGui::Checkbox("NoSpread", &g.NoSpread);
        ImGui::Checkbox("RangeBypass", &g.RangeBypass);
        break;
    default:
        break;
    }

    ImGui::EndChild();
    //---------------------------------------------------//
    ImGui::SameLine();
    //---// Right //--------------------------------------//
    ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    switch (Index)
    {
    case 0: // aim
        
        break;
    case 1: // visual
        ImGui::Text("ESP Setting");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SliderFloat("Distance", &g.ESP_MaxDistance, 50.f, 1000.f);

        ImGui::NewLine();
        ImGui::Spacing();

        ImGui::Text("  ESP Colors");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::ColorEdit4("NPC", &ESP_NPC.Value.x);
        ImGui::ColorEdit4("Player", &ESP_Player.Value.x);
        ImGui::ColorEdit4("Skeleton", &ESP_Skeleton.Value.x);
        break;
    case 2: // misc
        ImGui::Text("System");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Checkbox("StreamProof", &g.StreamProof);

        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();

        // Exit
        if (ImGui::Button("Exit", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
            g.Run = false;
        break;
    default:
        break;
    }

    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::End();
}

void Cheat::RenderESP()
{
    CPed* pLocal = &local;
    Matrix ViewMatrix = m.Read<Matrix>(viewport + 0x24C);

    if (!pLocal->Update())
        return;

    for (auto& ped : EntityList)
    {
        CPed* pEntity = &ped;

        if (!pEntity->Update())
            continue;

        float pDistance = GetDistance(pEntity->m_vPosition, pLocal->m_vPosition);

        if (pDistance >= g.ESP_MaxDistance)
            continue;

        // Box
        Vector2 pBase{}, pHead{}, pNeck{}, pLeftFoot{}, pRightFoot{};
        if (!WorldToScreen(ViewMatrix, pEntity->m_vPosition, pBase) || !WorldToScreen(ViewMatrix, pEntity->BoneList[HEAD], pHead) || !WorldToScreen(ViewMatrix, pEntity->BoneList[NECK], pNeck) || !WorldToScreen(ViewMatrix, pEntity->BoneList[LEFTFOOT], pLeftFoot) || !WorldToScreen(ViewMatrix, pEntity->BoneList[RIGHTFOOT], pRightFoot))
            continue;

        // ESP用にいくつかサイズを出しておく
        float HeadToNeck = pNeck.y - pHead.y;
        float pTop = pHead.y - (HeadToNeck * 2.5f);
        float pBottom = (pLeftFoot.y > pRightFoot.y ? pLeftFoot.y : pRightFoot.y) * 1.001f;
        float pHeight = pBottom - pTop;
        float pWidth = pHeight / 3.5f;
        float bScale = pWidth / 1.5f;
        ImColor color = pEntity->isPlayer() ? ESP_Player : ESP_NPC;

        // Line
        if (g.ESP_Line)
            DrawLine(ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom), ImVec2(pBase.x, pBottom), color, 1.f);

        // Box
        if (g.ESP_Box)
        {
            DrawLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x + pWidth, pTop), color, 1.f);
            DrawLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pBottom), color, 1.f);
            DrawLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pBottom), color, 1.f);
            DrawLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, 1.f);
        }

        // Skeleton
        if (g.ESP_Skeleton)
        {
            // Body
            for (int j = 0; j < 5; j++)
            {
                Vector3 skList[][2] = { { pEntity->BoneList[NECK], pEntity->BoneList[HIP] }, { pEntity->BoneList[NECK], pEntity->BoneList[LEFTHAND] },
                    { pEntity->BoneList[NECK], pEntity->BoneList[RIGHTHAND] }, { pEntity->BoneList[HIP], pEntity->BoneList[LEFTFOOT] }, { pEntity->BoneList[HIP], pEntity->BoneList[RIGHTFOOT] } };

                if (Vec3_Empty(skList[j][0]) || Vec3_Empty(skList[j][1]))
                    break;

                Vector2 ScreenB1{}, ScreenB2{};
                if (!WorldToScreen(ViewMatrix, skList[j][0], ScreenB1) || !WorldToScreen(ViewMatrix, skList[j][1], ScreenB2))
                    break;

                DrawLine(ImVec2(ScreenB1.x, ScreenB1.y), ImVec2(ScreenB2.x, ScreenB2.y), ESP_Skeleton, 1.f);
            }
        }

        // Healthbar
        if (g.ESP_HealthBar)
        {
            HealthBar((pBase.x - pWidth) - 5.f, pBottom, 2.f, -pHeight, pEntity->m_fHealth, pEntity->m_fMaxHealth);

            if (pEntity->m_fArmor > 0.f)
                ArmorBar((pBase.x + pWidth) + 3.f, pBottom, 2.f, -pHeight, pEntity->m_fArmor, 100);
        }

        // Distance
        if (g.ESP_Distance)
        {
            std::string dist = std::to_string((int)pDistance) + "m";
            String(ImVec2(pBase.x - ImGui::CalcTextSize(dist.c_str()).x / 2.f, pBottom), ImColor(1.f, 1.f, 1.f, 1.f), dist.c_str());
        }
    }
}