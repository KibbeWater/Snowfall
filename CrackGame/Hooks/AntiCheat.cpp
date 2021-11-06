#include "pch.h"

void __stdcall Hook::AntiCheat::hkCheatingDetected(CodeStage_AntiCheat_Detectors_ACTkDetectorBase_WallHackDetector__o* pThis, const MethodInfo_3A3D90* pMethod)
{
	static auto oCheatingDetected = static_cast<decltype(&hkCheatingDetected)>(pCheatingDetected);

	if (!G::bAnticheatDisabler && false)
		oCheatingDetected(pThis, pMethod);
}
