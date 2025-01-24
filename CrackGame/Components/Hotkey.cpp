//
// Created by kibbe on 1/18/2025.
//

#include "pch.h"

bool Components::Hotkey(const char* label, int* key, ImVec2 button_size) {
	ImGuiStorage* storage = ImGui::GetStateStorage();

	// Create unique IDs for this instance's state
	ImGuiID listening_id = ImGui::GetID((std::string(label) + "_listening").c_str());
	bool is_listening = storage->GetBool(listening_id, false);
	bool key_changed = false;

	ImGui::PushID(label);

	// Rest of the code remains the same, but replace static vars with our storage
	std::string button_text = is_listening ? "..." : (*key ? s_keyNames.at(*key) : "None");

	float textPad = 4;
	auto textSize = ImGui::CalcTextSize(button_text.c_str());

	auto minSize = textSize.x + textPad * 2;
	if (minSize > button_size.x) button_size.x = minSize;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - button_size.x));

	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw = ImGui::GetWindowDrawList();
	draw->AddRectFilled(p, p + button_size, IM_COL32(40, 40, 40, 255), 4);
	draw->AddText(ImVec2(
		p.x + (button_size.x / 2 - textSize.x / 2),
		p.y + (button_size.y / 2 - textSize.y / 2)),
		IM_COL32(255, 255, 255, 255),
		button_text.c_str());

	if (ImGui::InvisibleButton(button_text.c_str(), button_size)) {
		storage->SetBool(listening_id, true);
	}

	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Click to change hotkey");
	}

	if (is_listening) {
		if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
			*key = ImGuiKey_None;
			storage->SetBool(listening_id, false);
			key_changed = true;
		}

		for (const auto& [k, name] : s_keyNames) {
			if (k != ImGuiKey_Escape && ImGui::IsKeyPressed(static_cast<ImGuiKey>(k))) {
				*key = k;
				storage->SetBool(listening_id, false);
				key_changed = true;
				break;
			}
		}
	}

	ImGui::PopID();
	return key_changed;
}
