//
// Created by kibbe on 1/22/2025.
//

#include "pch.h"

bool Components::Button(const char *label, ImVec2 size, int flags) {
    ImDrawList* draw = ImGui::GetWindowDrawList();
    auto style = ImGui::GetStyle();

    auto p = ImGui::GetCursorScreenPos();

    auto color = IM_COL32(36, 89, 173, 255);

    auto textSize = ImGui::CalcTextSize(label);
    if (flags & ImGuiCustomButtonFlags_AutoResizeX) size.x = ImGui::GetContentRegionAvail().x;
    if (flags & ImGuiCustomButtonFlags_AutoResizeY) size.y = textSize.y + 8*2;

    auto clicked = ImGui::InvisibleButton(label, size);

    if (ImGui::IsItemHovered()) color = IM_COL32(33, 72, 133, 255);
    if (ImGui::IsItemActive()) color = IM_COL32(21, 48, 89, 255);

    draw->AddRectFilled(p, p + size, color, 8.0f);
    
    draw->AddText(p+ImVec2((size.x/2) - (textSize.x/2), (size.y/2) - (textSize.y/2)), ImGui::GetColorU32(ImGuiCol_Text), label);

    return clicked;
}
