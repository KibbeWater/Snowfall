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

// Thirdparty
#include "Thirdparty/Ntdll/ntdll.h"
#include "Thirdparty/MinHook/MinHook.h"

// Helpers
#include "Helpers/Math.h"
#include "Helpers/Memory.h"



