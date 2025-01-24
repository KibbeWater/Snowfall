//
// Created by kibbe on 1/18/2025.
//

#include "pch.h"

void Components::Checkbox(const char *label, bool *v) {
    ImGui::PushID(label);

    ImVec2 size = ImVec2(16, 16);

    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw = ImGui::GetWindowDrawList();

    if (ImGui::InvisibleButton(label, size)) *v = !*v;

    ImU32 color_bg = IM_COL32(40, 40, 40, 255);
    ImU32 color_hover = IM_COL32(50, 50, 50, 255);
    ImU32 color_accent = IM_COL32(66, 135, 245, 255);

    draw->AddRectFilled(p, ImVec2(p.x + size.y, p.y + size.y),
                        *v ? color_accent : (!ImGui::IsItemHovered() ? color_bg : color_hover), 4);

    auto textSize = ImGui::CalcTextSize(label);
    draw->AddText(
        ImVec2(
            p.x + size.y + 8,
            p.y + (size.y/2 - textSize.y/2)),
        IM_COL32(200, 200, 200, 255),
        label);

    ImGui::PopID();
}
