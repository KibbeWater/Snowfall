#pragma once

// Define some compile options
#define DEV_MODE true

// Vista min supported version
#define _WIN32_WINNT 0x0600 
#define WINVER 0x0600 

// Standard
#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

// Config
#include "config.h"
#include "globals.h"

// Thirdparty
#include "Thirdparty/Ntdll/ntdll.h"
#include "Thirdparty/MinHook/MinHook.h"

// GameSDK
#include "GameSDK/il2cpp.h"
#include "GameSDK/Other.h"
#include "GameSDK/Enums.h"

// Helpers
#include "Helpers/Math.h"
#include "Helpers/Memory.h"

// Hooks
#include "Hooks/Hooks.h"
#include "Hooks/PunchPlayers.h"
#include "Hooks/CameraShake.h"
#include "Hooks/PlayerMovement.h"
#include "Hooks/PlayerInventory.h"
#include "Hooks/PlayerStatus.h"
#include "Hooks/OnlinePlayerMovement.h"
#include "Hooks/AntiCheat.h"
#include "Hooks/GamemodeLights.h"
#include "Hooks/GamemodeRedLight.h"
#include "Hooks/GamemodeBombTag.h"
#include "Hooks/GamemodeTag.h"
#include "Hooks/LobbyManager.h"
#include "Hooks/GameManager.h"
#include "Hooks/ClientSend.h"
#include "Hooks/D3D11Hook.h"
#include "Hooks/InputHook.h"
#include "Hooks/ItemGun.h"

// ImGUI
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_impl_dx11.h"

// Menu
#include "Menu/Menu.h"
#include "Hooks/Chatbox.h"
#include "Hooks/PlayerInput.h"

// Features
