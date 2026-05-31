#pragma once
#include <imgui.h>

namespace LongDay{
    namespace Colors {

   // Text / neutral
    constexpr ImVec4 DIM       = { 0.47f, 0.51f, 0.58f, 1.f }; 
    constexpr ImVec4 PRIMARY   = { 0.88f, 0.87f, 0.84f, 1.f };

    // Machine states  
    constexpr ImVec4 WORKING     = { 0.24f, 0.43f, 0.07f, 1.f }; // #3e7312
    constexpr ImVec4 BROKEN      = { 0.64f, 0.18f, 0.18f, 1.f }; // #A32D2D
    constexpr ImVec4 MAINTENANCE = { 0.52f, 0.31f, 0.04f, 1.f }; // #854F0B
    constexpr ImVec4 IDLE        = { 0.47f, 0.51f, 0.58f, 1.f }; // same as DIM

    // Health bar
    constexpr ImVec4 HEALTH_GOOD = { 0.11f, 0.62f, 0.46f, 1.f }; // #1D9E75
    constexpr ImVec4 HEALTH_BAD  = { 0.89f, 0.29f, 0.29f, 1.f }; // #E24B4A

    // Log severity
    constexpr ImVec4 LOG_WARN    = { 0.73f, 0.46f, 0.09f, 1.f }; // #BA7517
    constexpr ImVec4 LOG_DANGER  = BROKEN;
    constexpr ImVec4 LOG_OK      = WORKING;

    // Product dot on conveyor
    constexpr ImVec4 PRODUCT_DOT = { 0.22f, 0.53f, 0.87f, 1.f }; // #378ADD

    // Background for ImGui child window
    constexpr ImVec4 BG_PRIMARY   = { 0.09f, 0.11f, 0.14f, 1.f };

    }
}