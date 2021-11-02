#include "pch.h"

void __stdcall Hook::GamemodeRedLight::hkRedLight(GameModeRedLight_o* pThis, float reactionTime, const MethodInfo* pMethod)
{
	static auto oRedLight = static_cast<decltype(&hkRedLight)>(pRedLight);

	G::bRedLightFreeze = true;

	oRedLight(pThis, reactionTime, pMethod);
}

void __stdcall Hook::GamemodeRedLight::hkGreenLight(GameModeRedLight_o* pThis, float reactionTime, const MethodInfo* pMethod)
{
	static auto oGreenLight = static_cast<decltype(&hkGreenLight)>(pGreenLight);

	G::bRedLightFreeze = false;

	oGreenLight(pThis, reactionTime, pMethod);
}
