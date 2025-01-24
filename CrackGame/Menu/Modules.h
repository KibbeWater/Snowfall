#pragma once

namespace Modules {
    inline void CheckboxHotkey(std::string label, std::string path, bool defaultValue) {
        auto enabled = Config::getConfig(path + "_enabled", defaultValue);
        Components::Checkbox(label.c_str(), enabled);
        ImGui::SameLine();
        auto hotkey = Config::getConfig(path + "_hotkey", static_cast<int>(ImGuiKey_None));
        Components::Hotkey((label + "##hotkey").c_str(), hotkey, ImVec2{ 30.0f, 15.0f });
    }

    inline void Separator(float height = 2.0f, ImVec2 paddingY = ImVec2()) {
        ImGuiStyle& style = ImGui::GetStyle();

        auto frameColor = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_WindowBg]);
        auto childPadding = 8.0f;
        auto itemSpacing = style.ItemSpacing;

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + paddingY.y);

        auto p = ImGui::GetCursorScreenPos();
        auto width = ImGui::GetContentRegionAvail().x;

        ImDrawList* draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            p - ImVec2(childPadding, 0),
            p + ImVec2(width + childPadding, height),
            frameColor
        );

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (height + paddingY.y) + itemSpacing.y);
    }

    inline bool CategoryButton(char* label, char icon, ImVec2 size) {
        ImDrawList* draw = ImGui::GetWindowDrawList();

		auto p = ImGui::GetCursorScreenPos();

        auto color = ImGui::GetColorU32(ImGuiCol_Button);
        draw->AddRectFilled(p, p + size, color, 6.0f);

        auto clicked = ImGui::InvisibleButton(label, size);

        return clicked;
    }

    inline bool CategoryButton(const char* label, const char* icon, ImVec2 size) {
        ImDrawList* draw = ImGui::GetWindowDrawList();

        auto p = ImGui::GetCursorScreenPos();

        auto color = IM_COL32(36, 89, 173, 255);

        auto clicked = ImGui::InvisibleButton(label, size);

        if (ImGui::IsItemHovered()) color = IM_COL32(33, 72, 133, 255);
        if (ImGui::IsItemActive()) color = IM_COL32(21, 48, 89, 255);

        draw->AddRectFilled(p, p + size, color, 8.0f);

        auto iconSize = ImGui::CalcTextSize(icon);
        draw->AddText(p + ImVec2(10, (size.y / 2) - (iconSize.y / 2)), ImGui::GetColorU32(ImGuiCol_Text), icon);

        auto textSize = ImGui::CalcTextSize(label);
        draw->AddText(p + ImVec2(10 + iconSize.x + 8, (size.y / 2) - (textSize.y / 2)), ImGui::GetColorU32(ImGuiCol_Text), label);

        return clicked;
    }

    inline void _section(const char* label, const std::function<void()>& header, const std::function<void()>& content) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(25, 25, 25, 255));

        if (ImGui::BeginChild(label, ImVec2(ImGui::GetContentRegionAvail().x, 0), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY, ImGuiWindowFlags_None)) {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));
            header();
            ImGui::PopStyleVar(1);

            content();
        }
        ImGui::EndChild();

        ImGui::PopStyleColor(1);
    }

    inline void RenderSectionHeaderless(const char* label, const std::function<void()>& content) {
        ImGui::PushID(label);

        _section(label, []() {
            },
            [content]() {
                content();
            });

        ImGui::PopID();
    }

    inline void RenderSection(const char* label, const std::function<void()>& content) {
        ImGui::PushID(label);

        _section(label, [label]() {
            ImGui::Text(label);
            Separator(2, ImVec2(0, 2));
            },
            [content]() {
                content();
            });

        ImGui::PopID();
    }

    inline void RenderFeaturelist(const std::function<void()>& lCol,
        const std::function<void()>& rCol) {
        ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 12.0f));
        if (ImGui::BeginTable("FeatTable", 2, ImGuiTableFlags_SizingStretchSame))
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            if (ImGui::BeginChild("RightCol1", ImGui::GetContentRegionAvail(), ImGuiChildFlags_None, ImGuiWindowFlags_None))
            {
                lCol();
                ImGui::EndChild();
            }

            ImGui::TableSetColumnIndex(1);
            if (ImGui::BeginChild("RightCol2", ImGui::GetContentRegionAvail(), ImGuiChildFlags_None, ImGuiWindowFlags_None))
            {
                rCol();
                ImGui::EndChild();
            }

            ImGui::EndTable();
            ImGui::PopStyleColor(1);
            ImGui::PopStyleVar(2);
        }
    }
}