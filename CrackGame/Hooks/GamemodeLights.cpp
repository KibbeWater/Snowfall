#include "pch.h"

void __stdcall Hook::GamemodeLights::hkToggleLights(GameModeLights_o* pThis, bool b, const MethodInfo* pMethod)
{
	static auto oToggleLights = static_cast<decltype(&hkToggleLights)>(pToggleLights);

	bool bLightsAlwaysOn = Config::get("gamemode_dorms_antidark", false);

	oToggleLights(pThis, bLightsAlwaysOn ? true : b, pMethod);
}
