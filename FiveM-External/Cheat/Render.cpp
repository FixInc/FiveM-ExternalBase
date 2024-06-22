#include "Cheat.h"
#include "..\Overlay\Overlay.h"

// Menu
const char* LineStartList[] = { "Local", "Screen Under", "Screen Center", "Screen Top" };
const char* SkeletonColorList[] = { "ESP", "User" };
const char* CrosshairList[] = { "Cross", "Circle" };

// Resource
int SkeletonBoneList[][2] = { { 7, 6 }, { 7, 5 }, { 7, 8 }, { 8, 3 }, { 8, 4 } };
std::vector<std::string> MenuFCList = { "Local", "AimBot", "Visual", "Game", "Setting" };

void Cheat::RenderInfo()
{
    // W
    std::string text = "FiveM | " + std::to_string((int)ImGui::GetIO().Framerate) + "FPS";
    String(ImVec2(8.f, 8.f), ImColor(1.f, 1.f, 1.f, 1.f), text.c_str());

    // InitAddress
    world = m.Read<uintptr_t>(m.BaseAddress + offset::GameWorld);
    local.ptr = m.Read<uintptr_t>(world + 0x8);
    viewport = m.Read<uintptr_t>(m.BaseAddress + offset::ViewPort);

    // Crosshair
    if (g.Crosshair)
    {
        switch (g.CrosshairType)
        {
        case 0:
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(((float)g.GameRect.right / 2.f + 4), ((float)g.GameRect.bottom / 2.f)), ImVec2(((float)g.GameRect.right / 2.f + 10), ((float)g.GameRect.bottom / 2.f)), ImColor(1.f, 1.f, 1.f, 1.f), 1);
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(((float)g.GameRect.right / 2.f - 4), ((float)g.GameRect.bottom / 2.f)), ImVec2(((float)g.GameRect.right / 2.f - 10), ((float)g.GameRect.bottom / 2.f)), ImColor(1.f, 1.f, 1.f, 1.f), 1);
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(((float)g.GameRect.right / 2.f), ((float)g.GameRect.bottom / 2.f + 4)), ImVec2(((float)g.GameRect.right / 2.f), ((float)g.GameRect.bottom / 2.f + 10)), ImColor(1.f, 1.f, 1.f, 1.f), 1);
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(((float)g.GameRect.right / 2.f), ((float)g.GameRect.bottom / 2.f - 4)), ImVec2(((float)g.GameRect.right / 2.f), ((float)g.GameRect.bottom / 2.f - 10)), ImColor(1.f, 1.f, 1.f, 1.f), 1);
            break;
        case 1:
            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 2, ImColor(1.f, 1.f, 1.f, 1.f), NULL);
            break;
        default:
            break;
        }
    }
}

void Cheat::RenderMenu()
{
    // Setup
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImGuiStyle& style = ImGui::GetStyle();
    static int Index = 0;

    ImGui::SetNextWindowBgAlpha(0.975f);
    ImGui::SetNextWindowSize(ImVec2(650.f, 450.f));
    ImGui::Begin("FiveM [ EXTERNAL ]", &g.ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    //---// Clild 0 //-----------------------------------//
    ImGui::BeginChild("##SelectChild", ImVec2(150.f, ImGui::GetContentRegionAvail().y), false);

    ImGui::NewLine();

    for (int i = 0; i < MenuFCList.size(); i++)
    {
        if (ImGui::Button(MenuFCList[i].c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 35.f)))
            Index = i;
    }

    ImGui::EndChild();
    //---// Clild 0 //-----------------------------------//

    ImGui::SameLine();

    //---// Clild 1 //-----------------------------------//
    ImGui::BeginChild("##ContextChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    //---// Left //--------------------------------------//
    ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 16.f, ImGui::GetContentRegionAvail().y), false);

    switch (Index)
    {
    case 0: // local
        ImGui::Checkbox("GodMode", &g.GodMode);
        ImGui::Checkbox("FastRun", &g.FastRun);
        break;
    case 1: // aim

        break;
    case 2: // visual
        ImGui::Text("Visual");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Player ESP", &g.PlayerESP);

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
    case 3: // game
        ImGui::Text("System");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Checkbox("StreamProof", &g.StreamProof);
        ImGui::Checkbox("Crosshair", &g.Crosshair);
        ImGui::Combo("Type", &g.CrosshairType, CrosshairList, IM_ARRAYSIZE(CrosshairList));
        break;
    case 4: // setting
        
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
    case 0: // local
        break;
    case 1: // aim
        /* [+] KeyBinder Example
        if (ImGui::Button(g.KeyBinding && g.BindingID == 1 ? "< Press Any Key >" : KeyNames[g.AimKey0], ImVec2(215.f, 20.f)))
        {
            g.KeyBinding = true;
            g.BindingID = 1;
            std::thread([&]() {this->KeyBinder(g.AimKey0); }).detach();
        }
        */
        break;
    case 2: // visual
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
    case 3: // game
        break;
    case 4: // setting
        // Exit
        if (ImGui::Button("Exit", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
            g.Run = false;
        break;
    default:
        break;
    }

    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::End();
}

// NY - 5300, -5000, 83
void Cheat::RenderESP()
{
    CPed* pLocal = &local;
    Matrix ViewMatrix = m.Read<Matrix>(viewport + 0x24C);

    // Access EntityList
    uintptr_t ReplayInterface = m.Read<uintptr_t>(m.BaseAddress + offset::ReplayInterface);
    uintptr_t EntityListPtr = m.Read<uintptr_t>(ReplayInterface + 0x18);
    uintptr_t EntityList = m.Read<uintptr_t>(EntityListPtr + 0x100);

    for (int i = 0; i < 256; i++) 
    {
        CPed ped, *pEntity = &ped;
        uintptr_t player = m.Read<uintptr_t>(EntityList + (i * 0x10));

        if (!pEntity->GetPlayer(player))
            continue;
        
        // Checks
        if (player == pLocal->ptr)
            continue;
        else if (!pLocal->Update())
            continue;
        else if (!pEntity->Update())
            continue;

        float pDistance = GetDistance(pEntity->m_vPosition, pLocal->m_vPosition);

        if (pDistance >= g.ESP_MaxDistance)
            continue;

        Vector3 gHead = pEntity->GetBonePosition(0);
        Vector3 gNeck = pEntity->GetBonePosition(7);
        Vector3 gFoot1 = pEntity->GetBonePosition(1);
        Vector3 gFoot2 = pEntity->GetBonePosition(2);

        // Box—p
        Vector2 pBase{}, pFoot1{}, pFoot2{}, pHead{}, pNeck{}, pLocalPos{};
        if (Vec3_Empty(gHead) || Vec3_Empty(gNeck) || Vec3_Empty(gFoot1) || Vec3_Empty(gFoot2))
            continue;
        else if (!WorldToScreen(ViewMatrix, pEntity->m_vPosition, pBase) || !WorldToScreen(ViewMatrix, gFoot1, pFoot1) || !WorldToScreen(ViewMatrix, gFoot2, pFoot2) || !WorldToScreen(ViewMatrix, gHead, pHead) || !WorldToScreen(ViewMatrix, gNeck, pNeck) || !WorldToScreen(ViewMatrix, pLocal->m_vPosition, pLocalPos))
            continue;

        // ESP Resource
        float HeadToNeck = pNeck.y - pHead.y;
        float pTop = pHead.y - (HeadToNeck * 2.5f);
        float pBottom = (pFoot1.y > pFoot2.y ? pFoot1.y : pFoot2.y) * 1.001f;
        float pHeight = pBottom - pTop;
        float pWidth  = pHeight / 3.5f;
        float bScale = pWidth / 1.5f;
        ImColor color = pEntity->IsPlayer() ? ESP_Player : ESP_NPC;

        // Line
        if (g.ESP_Line)
            DrawLine(ImVec2(pLocalPos.x, pLocalPos.y), ImVec2(pBase.x, pBottom), color, 1.f);

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
                Vector3 bone1 = pEntity->GetBonePosition(SkeletonBoneList[j][0]);
                Vector3 bone2 = pEntity->GetBonePosition(SkeletonBoneList[j][1]);

                if (Vec3_Empty(bone1) || Vec3_Empty(bone2))
                    break;

                Vector2 ScreenB1{}, ScreenB2{};
                if (!WorldToScreen(ViewMatrix, bone1, ScreenB1) || !WorldToScreen(ViewMatrix, bone2, ScreenB2))
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