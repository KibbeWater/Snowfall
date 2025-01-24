#include "pch.h"

void __stdcall Hook::GlassBreak::hkOnTriggerEnter(GlassBreak_o* pThis, UnityEngine_Collider_o* collider, const MethodInfo* pMethod) {
	static auto oOnTriggerEnter = static_cast<decltype(&hkOnTriggerEnter)>(pOnTriggerEnter);

	bool bPreventGlassBreak = Config::get("gamemode_glass_antibreak", false);

	if(bPreventGlassBreak)
		oOnTriggerEnter(pThis, collider, pMethod);
}
