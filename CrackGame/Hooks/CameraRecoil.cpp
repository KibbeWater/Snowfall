#include "pch.h"

void __stdcall Hook::CameraRecoil::hkAddRecoil(UnityEngine_Vector2_o recoil, const MethodInfo* pMethod) {
	static auto oAddRecoil = static_cast<decltype(&hkAddRecoil)>(pAddRecoil);

	if (!F::bNoRecoil)
		oAddRecoil(recoil, pMethod);
}
