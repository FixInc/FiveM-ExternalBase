#include "Cheat.h"

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