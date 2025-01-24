#include "pch.h"

using namespace Modules;

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

void RenderVisual() {
    RenderFeaturelist(
        []() {
            RenderSection("ESP", []() {
                CheckboxHotkey("ESP", "visual_esp_state", false);

                Components::Checkbox("Box",
                    Config::getConfig("visual_esp_box", true));
                });
        },
        []() {
            RenderSectionHeaderless("global", []() {
                CheckboxHotkey("Tracers", "visual_tracers", false);

                });
        });
}

void RenderCombat() {
    RenderFeaturelist(
        []() {
            RenderSectionHeaderless("global", []() {
                CheckboxHotkey("Godmode", "combat_godmode", false);

                Components::Checkbox("Fast Swing",
                    Config::getConfig("combat_fastswing", false));
                });
            RenderSection("Ranged", []() {
                Components::Checkbox("Auto Fire",
                    Config::getConfig("combat_autofire", false));

                CheckboxHotkey("Rapid Fire", "combat_rapidfire", false);

                Components::Checkbox("Infinite Ammo",
                    Config::getConfig("combat_infiniteammo", false));

                Components::Checkbox("No Recoil",
                    Config::getConfig("combat_norecoil", false));

                });
        },
        []() {
            RenderSection("Throwing", []() {
                CheckboxHotkey("Auto Snowball Refill", "combat_autosnowball", false);

                Components::Checkbox("No Throw Cooldown",
                    Config::getConfig("combat_fastthrow", false));
                });
        });
}

void RenderMovement() {
	RenderFeaturelist(
		[]() {
			RenderSectionHeaderless("global", []() {
				CheckboxHotkey("Speedhack", "movement_speedhack", false);
                ImGui::SliderInt("Speed", Config::getConfig("movement_speedhack_speed", 100), 100, 1000);

                ImGui::Spacing();

				Components::Checkbox("Air Jump",
					Config::getConfig("movement_airjump", false));

                // Doesn't work
				// Components::Checkbox("No Fall Damage",
					// Config::getConfig("movement_nofalldamage", false));
				});
			RenderSection("Teleport", []() {
				CheckboxHotkey("Click TP", "movement_clicktp", false);
				});
		},
		[]() {
			RenderSection("Misc", []() {
				bool* bKnockback = Config::getConfig("movement_antikb", false);
				Components::Checkbox("Anti-Knockback", bKnockback);
                if (*bKnockback)
					Components::Checkbox("Advanced Anti-Knockback", 
                        Config::getConfig("movement_advancedantikb", false));

				});
		});
}

void RenderGamemode() {
	RenderFeaturelist(
		[]() {
			RenderSection("Red light Green light", []() {
				CheckboxHotkey("Freeze", "gamemode_redlight_freeze", false);
				});

            RenderSection("Dorms", []() {
                Components::Checkbox("Lights always on", 
                    Config::getConfig("gamemode_dorms_antidark", false));
                });
		},
		[]() {
			RenderSection("Misc", []() {
				Components::Checkbox("Anti-Freeze",
					Config::getConfig("gamemode_nofreeze", false));
				});
            RenderSection("Glass Break", []() {
                Components::Checkbox("Prevent glass break", 
                    Config::getConfig("gamemode_glass_antibreak", false));
                if (Components::Button("Break glass"))
                    GameAPI::BreakAll();
                });
		});
}

void RenderItems() {
	RenderFeaturelist(
		[]() {
			RenderSection("Item Giver", []() {
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

                if (Components::Button("Give Weapon")) {
                    auto item = GameAPI::GetItemByID(selectedWeapon);
                    GameAPI::ForceGiveItem(item);
                }

				});
		},
		[]() {
		});
}

void RenderLobby() {
	RenderFeaturelist(
		[]() {
			RenderSection("Lobby", []() {

                bool* bMaxPlayesOverride = Config::getConfig("lobby_maxplayers_on", false);
                Components::Checkbox("Max Player Override", 
                    bMaxPlayesOverride);
                if (*bMaxPlayesOverride)
                    ImGui::SliderInt("Max Players", Config::getConfig("lobby_maxplayers_count", 40), 40, 5000);
                if (Components::Button("Start Game"))
                    GameAPI::StartGames();
				});
		},
		[]() {
			RenderSectionHeaderless("global", []() {
				Components::Checkbox("Hacker Prevention",
					Config::getConfig("lobby_anticheat", true));
				});
		});
}

void RenderMisc() {
	RenderFeaturelist(
		[]() {
			RenderSection("Misc", []() {
                CheckboxHotkey("Lagswitch", "misc_lagswitch", false);
                Components::Checkbox("Command Handler", 
                    Config::getConfig("misc_commandhandler", false));

				ImGui::Separator();

                if (Components::Button("Complete Daily"))
                    GameAPI::CompleteDaily();

                ImGui::Separator();

                Components::Checkbox("Chatspammer", 
                    Config::getConfig("misc_chatspammer_on", false));
                ImGui::InputText("Spam Text", 
                    Config::getConfig("misc_chatspammer_msg", std::string("Snowfall on top")));
				});
		},
		[]() {
			RenderSection("Debug", []() {
				Components::Checkbox("Debug",
					Config::getConfig("misc_debug", false));
				});
		});
}

void RenderConfig() {
	RenderFeaturelist(
		[]() {
            std::string path = FS::GetLuaFile("");
            RenderSectionHeaderless("global", [&]() {
                
                ImGui::Text("Lua Path: %s", path.c_str());

				if (Components::Button("Reload Lua")) {
                    auto oldState = G::vLuaState;
                    G::oCallbackManager->clear_callbacks();
                    G::vLuaState = new sol::state();
                    LuaH::initState(G::vLuaState);
                    delete oldState;
                }
				});

			RenderSection("Lua", [&]() {
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
				});
		},
		[]() {
			RenderSection("Debug", []() {
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));
                ImGui::Text("Config Name");

                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(35, 35, 35, 255));
                static std::string configName = "config";
                ImGui::PushItemWidth(-1);
                ImGui::InputText("Config Name", &configName);
                ImGui::PopItemWidth();
                ImGui::PopStyleVar(2);
                ImGui::PopStyleColor(1);

                ImGui::Spacing();

                if (Components::Button("Save Config") && !configName.empty()) Config::saveConfig(configName);
                if (Components::Button("Load Config") && !configName.empty()) Config::loadConfig(std::string(configName));
				});
		});
}

void Menu::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(15, 10));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(20, 20, 40, 255));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(50, 50, 80, 255));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(70, 70, 120, 255));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(20, 20, 20, 255));
	ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0));

	ImGui::GetIO().MouseDrawCursor = Menu::bIsOpen;

    static MenuTab activeTab = MenuTab::NONE;
    if (Menu::bIsOpen) {
        ImGui::SetNextWindowSize(ImVec2(700, 500));
        if (ImGui::Begin("Snowfall", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
            {
                // Left Col
                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(25, 25, 25, 255));
                if (ImGui::BeginChild("Sidebar", ImVec2(175, ImGui::GetContentRegionAvail().y))) {
                    float userSizeY = 60;
                    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None; // ImGuiWindowFlags_HorizontalScrollbar;

                    {
                        if (ImGui::BeginChild("FeatL", ImVec2(175, ImGui::GetContentRegionAvail().y - (userSizeY + 10)), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY, window_flags)) {
                            int clickedButton = -1;

                            Components::FileImage(FS::GetAsset("logo.png"), ImVec2(-1, -1), 1, ImGuiImageFlags_AutoResizeX);

                            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));
                            if (CategoryButton("Visual", "\xEE\x80\x80", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::VISUAL;
                            if (CategoryButton("Combat", "\xEE\x80\x82", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::COMBAT;
							if (CategoryButton("Movement", "\xEE\x80\x83", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::MOVEMENT;
							if (CategoryButton("Gamemode", "\xEE\x80\x83", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::GAMEMODE;
							if (CategoryButton("Items", "\xEE\x80\x83", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::ITEMS;
							if (CategoryButton("Lobby", "\xEE\x80\x83", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::LOBBY;
                            if (CategoryButton("Misc", "\xEE\x80\x85", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::MISC;
							if (CategoryButton("Config", "\xEE\x80\x81", ImVec2(ImGui::GetContentRegionAvail().x, 35))) clickedButton = MenuTab::CONFIG;
                            ImGui::PopStyleVar(1);

                            if (clickedButton != -1) {
                                if (clickedButton == activeTab) {
                                    activeTab = MenuTab::NONE;
                                }
                                else if (clickedButton != MenuTab::NONE) { //  lalalalalal "condition is always true" NO IT'S NOT???
                                    activeTab = static_cast<MenuTab>(clickedButton);
                                }
                            }
                        }
                        ImGui::EndChild();
                    }

                    {
                        if (ImGui::BeginChild("UserCard", ImVec2(175, userSizeY), ImGuiChildFlags_Border, ImGuiWindowFlags_None)) {
                            Components::FileImage(FS::GetAsset("steamAvatar.jpg"), ImVec2(-1, -1), 8, ImGuiImageFlags_AutoResizeY);
                            ImGui::SameLine();

                            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 2));
                            ImGui::BeginGroup(); {
                                ImGui::Text("KibbeWater");
                                ImGui::Text("456 Days");
                            } ImGui::EndGroup();
                            ImGui::PopStyleVar(1);
                        }
                        ImGui::EndChild();
                    }
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(1);

                ImGui::SameLine();

                // Right Col
                if (ImGui::BeginChild("rCol", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Borders)) {
                    switch (activeTab) {
                    case MenuTab::NONE:
                        break;
                    case MenuTab::VISUAL:
                        RenderVisual();
                        break;
                    case MenuTab::COMBAT:
                        RenderCombat();
                        break;
					case MenuTab::MOVEMENT:
						RenderMovement();
						break;
					case MenuTab::GAMEMODE:
						RenderGamemode();
						break;
					case MenuTab::ITEMS:
						RenderItems();
						break;
					case MenuTab::LOBBY:
						RenderLobby();
						break;
					case MenuTab::MISC:
						RenderMisc();
						break;
					case MenuTab::CONFIG:
						RenderConfig();
						break;
                    }
                }
                ImGui::EndChild();
            }

            ImGui::PopStyleVar(1);
        }
        ImGui::End();
    }

    // Pop styles
    ImGui::PopStyleColor(6);
    ImGui::PopStyleVar(4);
}
