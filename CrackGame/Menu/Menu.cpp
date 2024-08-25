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
				ImGui::Checkbox("Auto-Clicker", &F::bAutoClicker);
				ImGui::Checkbox("Command Handler", &F::bCommandHandler);
				ImGui::Spacing();
				if (ImGui::Button("Complete Daily"))
					GameAPI::CompleteDaily();
				ImGui::Checkbox("Chatspammer", &F::bChatSpammer);
				ImGui::InputText("Spam Text", F::sSpammerMsg, IM_ARRAYSIZE(F::sSpammerMsg));
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Combat"))
			{
				ImGui::Checkbox("Godmode", &F::bGodmode);
				ImGui::Checkbox("Fast Swing", &F::bFastSwing);
				ImGui::Checkbox("No Throw Cooldown", &F::bFastThrow);
				ImGui::Checkbox("Auto Snowball Refill", &F::bAutoSnowballRefill);
				ImGui::Checkbox("Infinite Ammo", &F::bInfAmmo);
				ImGui::Checkbox("No Recoil", &F::bNoRecoil);
				ImGui::Checkbox("Rapid Fire", &F::bRapidFire);
				/*ImGui::Checkbox("Reach", &F::bReach);
				if (F::bReach)
					ImGui::SliderFloat("Reach Slider", &F::fReachDist, 2.5, 100);*/
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Movement"))
			{
				ImGui::Checkbox("Speedhack", &F::bSpeedhack);
				if (F::bSpeedhack)
					ImGui::SliderInt("Speed", &F::iSpeedPercent, 100, 1000);
				ImGui::Checkbox("AirJump", &F::bAirJump);
				ImGui::Checkbox("Anti-Knockback", &F::bAntiKnockback);
				if (F::bAntiKnockback)
					ImGui::Checkbox("Advanced Anti-Knockback", &F::bAdvancedAntiKB);
				/*ImGui::Checkbox("NoSlide", &F::bNoSlide);*/
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
				#ifdef _DEBUG
				if (ImGui::TreeNode("Bomb Tag"))
				{
					ImGui::Checkbox("Anti-Bomb Tag", &F::bAntiBombTag);
					ImGui::TreePop();
				}
				#endif
				if (ImGui::TreeNode("Dorms"))
				{
					ImGui::Checkbox("Lights always on", &F::bLightsAlwaysOn);
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Glass Break")) {
					ImGui::Checkbox("Prevent glass breaking", &F::bPreventGlassBreak);
					if (ImGui::Button("Break Glass"))
						GameAPI::BreakAll();
					ImGui::TreePop();
				}
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Item Giver"))
			{
				static const char* curItem = "Rifle (BANNABLE)";
				static int selectedWeapon = 0;
				const char* items[] = { "Rifle (BANNABLE)", "Pistol", "Revolver", "Shotgun (BANNABLE)", "Bat", "Bomb", "Katana", "Knife", "Pipe", "Snowball", "Stick" };

				if (ImGui::BeginCombo("Weapon", curItem)) {
					for (int n = 0; n < IM_ARRAYSIZE(items); n++) { // Loop through all weapons
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
					auto item = GameAPI::GetItemByID(selectedWeapon);
					GameAPI::ForceGiveItem(item);
				}
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Lobby")) {
				ImGui::Checkbox("Hacker Prevention", &F::bHackerPrevention);
				ImGui::Checkbox("Max Player Override", &F::bMaxPlayersOverride);
				if (F::bMaxPlayersOverride)
					ImGui::SliderInt("Max Players", &F::iMaxPlayersCount, 40, 5000);
				if (ImGui::Button("Start Game"))
					GameAPI::StartGames();
			}
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("Lua")) {
				// List all .lua files in DATA_PATH\Lua
				std::string path = GameAPI::GetLuaPath();
				ImGui::Text("Lua Path: %s", path.c_str());
				if (ImGui::Button("Reload LUA environment")) {
					auto oldState = G::vLuaState;
					G::oCallbackManager->clear_callbacks();
					G::vLuaState = new sol::state();
					LuaH::initState(G::vLuaState);
					delete oldState;
				}
				ImGui::Spacing();
				ImGui::Text("Lua Scripts:");
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					std::string filename = entry.path().filename().string();
					if (filename.find(".lua") != std::string::npos && filename.find("autorun") == std::string::npos) {
						if (ImGui::Button(filename.c_str())) {
							// Get the file contents
							std::ifstream file(entry.path());
							std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
							file.close();

							G::vLuaState->safe_script(content, &sol::script_pass_on_error);
						}
					}
				}
			}
		}

		#ifdef _DEBUG
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Developer (EXPERIMENTAL)")) {
			ImGui::Checkbox("Debug Logging", &F::bDebug);
			ImGui::Checkbox("Crasher", &F::bCrasher);
			ImGui::Checkbox("Fake Player Count", &F::bFakePlayers);
			if (F::bFakePlayers)
				ImGui::SliderInt("Fake Players", &F::iFakePlayers, 0, 1000);
			if (ImGui::Button("Tiles"))
				GameAPI::TakeAllTiles();
			if (ImGui::Button("Dump GameObjects")) {
				Unity::il2cppClass* m_pSystemTypeClass = IL2CPP::Class::Find("UnityEngine.GameObject");
				auto m_pSystemType = IL2CPP::Class::GetSystemType(m_pSystemTypeClass);
				auto m_pObjects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(m_pSystemType);

				Unity::il2cppClass* m_pComponentTypeClass = IL2CPP::Class::Find("UnityEngine.Component");
				auto m_pComponentType = IL2CPP::Class::GetSystemType(m_pComponentTypeClass);

				ofstream file;
				file.open("dump.txt");

				for (uintptr_t u = 0U; m_pObjects->m_uMaxLength > u; ++u) {
					auto m_pObject = m_pObjects->At(u);
					file << m_pObject->GetName()->ToString() << std::endl;

					/* Unity::il2cppArray<Unity::CComponent*>* m_pComponents = m_pObject->GetComponents(m_pComponentType);
					for (uintptr_t i = 0U; m_pComponents->m_uMaxLength > i; ++i)
						file << "- " << m_pComponents->At(i)->GetName()->ToString() << std::endl; */
				}

				file.close();
			}

			if (ImGui::Button("Send to Space"))
				F::bFlingAll = true;
			if (ImGui::Button("Create Prompt"))
				GameAPI::Prompt("Snowfall", "Hooked and ready for use!");
			if (ImGui::Button("Create Alert"))
				GameAPI::Alert("[Snowfall] Hooked and ready for use!");
			ImGui::Checkbox("Fly", &F::bFly);
			ImGui::Checkbox("Block Item Removal", &F::bBlockItemRemoval);
		}
		#endif

		ImGui::End();
	}
}
