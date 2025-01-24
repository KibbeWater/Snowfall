#include "pch.h"

void __stdcall Hook::CameraRecoil::hkAddRecoil(UnityEngine_Vector2_o recoil, const MethodInfo* pMethod) {
	static auto oAddRecoil = static_cast<decltype(&hkAddRecoil)>(pAddRecoil);

	if (!Config::get("combat_norecoil", false))
		oAddRecoil(recoil, pMethod);
}
