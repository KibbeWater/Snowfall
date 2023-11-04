#pragma once

// Define some compile options
#define DEV_MODE true
#define COMMAND_PREFIX '!'

// Vista min supported version
#define _WIN32_WINNT 0x0600 
#define WINVER 0x0600 

// Standard
#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <d3d11.h>
#include <mutex>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdint>

// Config
#include "config.h"

// Helpers
#include "Helpers/Math.h"
#include "Helpers/Memory.h"

// Thirdparty
#include "Thirdparty/Ntdll/ntdll.h"
#include "Thirdparty/MinHook/MinHook.h"
#include "Thirdparty/Resolver/IL2CPP_Resolver.hpp"

// GameSDK
#include "GameSDK/il2cpp.h"
#include "GameSDK/Enums.h"
#include "SDK/Vector3.h"
#include "GameSDK/Other.h"
#include "GameSDK/CommandHandler.h"

// SDK
#include "globals.h"

// Hooks
#include "Hooks/Hooks.h"
#include "Hooks/PunchPlayers.h"
#include "Hooks/PlayerMovement.h"
#include "Hooks/PlayerInventory.h"
#include "Hooks/PlayerStatus.h"
#include "Hooks/OnlinePlayerMovement.h"
#include "Hooks/AntiCheat.h"
#include "Hooks/GamemodeLights.h"
#include "Hooks/GamemodeRedLight.h"
#include "Hooks/GamemodeBombTag.h"
#include "Hooks/GamemodeHat.h"
#include "Hooks/GamemodeTag.h"
#include "Hooks/LobbyManager.h"
#include "Hooks/GameManager.h"
#include "Hooks/ClientSend.h"
#include "Hooks/D3D11Hook.h"
#include "Hooks/InputHook.h"
#include "Hooks/ItemGun.h"
#include "Hooks/ItemMelee.h"
#include "Hooks/SteamPacketManager.h"
#include "Hooks/Chatbox.h"
#include "Hooks/PlayerInput.h"
#include "Hooks/CameraRecoil.h"
#include "Hooks/ItemSnowball.h"
#include "Hooks/SnowballPileInteract.h"
#include "Hooks/SteamMatchmaking.h"
#include "Hooks/ClientHandle.h";
#include "Hooks/GlassBreak.h"

// ImGUI
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_stdlib.h"

// Menu
#include "Menu/Menu.h"

// Features
