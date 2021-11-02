#pragma once

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
#include "Hooks/OnlinePlayerMovement.h"
#include "Hooks/AntiCheat.h"
#include "Hooks/GamemodeLights.h"
#include "Hooks/GamemodeRedLight.h"
#include "Hooks/PlayerStatus.h"
#include "Hooks/LobbyManager.h"
#include "Hooks/GameManager.h"

// Features
#include "Features/Punch.h"