#include "pch.h"

using namespace ImGui;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Menu::Render()
{
	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool auto_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = true;
	static bool start_pos_set = false;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.61f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	//colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

	ImGuiWindowFlags	window_flags = 0;
	if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
	if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowSize(ImVec2(450, 600));
	if (!start_pos_set) { ImGui::SetNextWindowPos(ImVec2(25, 25)); start_pos_set = true; }

	ImGui::GetIO().MouseDrawCursor = Menu::bIsOpen;

	if (Menu::bIsOpen)
	{
		ImGui::Begin("Snowfall", &Menu::bIsOpen, window_flags);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
		ImGui::PushItemWidth(-140);

		{
			if (ImGui::CollapsingHeader("General"))
			{
				ImGui::Checkbox("Disable pre-game freeze", &F::bDisablePregameFreeze);
				ImGui::Checkbox("Lagswitch", &F::bLagSwitch);
				ImGui::Spacing();
				if (ImGui::Button("Complete Daily"))
					GameAPI::CompleteDaily();
				if (ImGui::Button("Reset Quest Countdown")) {
					PlayerSave_o save = *GameAPI::GetSaveManager()->static_fields->Instance->fields.state;
					save.fields.nextQuestAvailableTime.fields.dateData = 0;
					save.fields.isQuestComplete = false;
					save.fields.currentQuest++;
				}
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Combat"))
			{
				ImGui::Checkbox("Godmode", &F::bGodmode);
				ImGui::Checkbox("Fast Swing", &F::bFastSwing);
				ImGui::Checkbox("Infinite Ammo", &F::bInfAmmo);
				ImGui::Checkbox("Reach", &F::bReach);
				if (F::bReach)
					ImGui::SliderFloat("Reach Slider", &F::fReachDist, 2.5, 100);
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Movement"))
			{
				ImGui::Checkbox("Speedhack", &F::bSpeedhack);
				if (F::bSpeedhack)
					ImGui::SliderInt("Speed", &F::iSpeedPercent, 100, 1000);
				ImGui::Checkbox("AirJump", &F::bAirJump);
				ImGui::Checkbox("Anti-Knockback", &F::bAntiKnockback);
				ImGui::Checkbox("NoSlide", &F::bNoSlide);
				ImGui::Checkbox("Click TP (Mouse3)", &F::bClickTP);
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Gamemodes"))
			{
				if (ImGui::TreeNode("Red Light Green Light"))
				{
					ImGui::Checkbox("Red Light freeze", &F::bRedGreenProtection);
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Bomb Tag"))
				{
					ImGui::Checkbox("Anti-Bomb Tag", &F::bAntiBombTag);
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Dorms"))
				{
					ImGui::Checkbox("Lights always on", &F::bLightsAlwaysOn);
					ImGui::TreePop();
				}
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Item Giver"))
			{
				static const char* curItem = "Rifle (BANNABLE)";
				static int selectedWeapon = 0;
				const char* items[] = { "Rifle (BANNABLE)", "Pistol", "Shotgun (BANNABLE)", "Bat", "Bomb", "Katana", "Knife", "Pipe", "Stick" };

				if (ImGui::BeginCombo("Weapon", curItem)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) { //Loop through all weapons
						bool isSelected = (curItem == items[n]);
						if (ImGui::Selectable(items[n], isSelected)) {
							curItem = items[n];
							selectedWeapon = n;
						}
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (ImGui::Button("Give Weapon")) {
					GameAPI::ForceGiveItem(GameAPI::GetItemByID(selectedWeapon));
				}
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Lobby"))
			{
				ImGui::Checkbox("Max Player Override", &F::bMaxPlayersOverride);
				if (F::bMaxPlayersOverride)
					ImGui::SliderInt("Max Players", &F::iMaxPlayersCount, 40, 5000);
			}
		}
		#ifdef DEBUG
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Developer (EXPERIMENTAL)"))
		{
			if (ImGui::Button("Dump GameObjects")) {
				auto m_pObjects = Unity::Object::FindObjectsOfType<Unity::CGameObject>("UnityEngine.GameObject");
				ofstream file;
				file.open("dump.txt");
				for (uintptr_t u = 0U; m_pObjects->m_uMaxLength > u; ++u)
				{
					Unity::CGameObject* m_pObject = m_pObjects->m_tValues[u];

					file << m_pObject->GetName()->ToString().c_str();

					file << "\n";
				}
				file.close();
			}
				
			if (ImGui::Button("Respawn"))
				GameAPI::RespawnPlayer(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.cameraRot);
			if (ImGui::Button("Spam packets")) {
				for (size_t i = 0; i < 30; i++)
				{
					GameAPI::DamagePlayer(213, i, 69, 69, GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.cameraRot);
				}
			}
			ImGui::Checkbox("Fly", &F::bFly);
		}
		#endif

		

		ImGui::End();
	}
}