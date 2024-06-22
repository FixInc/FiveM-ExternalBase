#pragma once
#include <Windows.h>

struct Globals
{
    // System
    bool Run = false;
    bool ShowMenu = false;

    // GameData
    HWND GameHwnd;
    RECT GameRect{};
    POINT GamePoint{};

    // Visual
    bool PlayerESP = true;
    bool ESP_Box = true;
    bool ESP_Line = false;
    bool ESP_Distance = true;
    bool ESP_HealthBar = true;
    bool ESP_Skeleton = true;
    float ESP_MaxDistance = 1000.f;

    // System
    bool StreamProof = false;
    bool Crosshair = false;
    int CrosshairType = 0;
    int RainbowRate = 25;

    // Misc
    bool GodMode = false;
    bool FastRun = false;

    // Key
    int MenuKey = VK_INSERT;
    int AimKey0 = VK_RBUTTON;
    int AimKey1 = VK_LBUTTON;

    // KeyBinder
    bool KeyBinding = false;
    int BindingID = 0;
};

extern bool IsKeyDown(int VK);
extern Globals g;