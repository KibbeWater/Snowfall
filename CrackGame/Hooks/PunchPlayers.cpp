#include "pch.h"

#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))


void __stdcall Hook::PunchPlayers::hkPunch(PunchPlayers_o* pThis, const MethodInfo* pMethod)
{
	static auto oPunch = static_cast<decltype(&hkPunch)>(pPunch);
	static float* p_fReach = (float*)MEM::PatternScanRel("GameAssembly.dll", "F3 0F 10 15 ? ? ? ? 48 8D 55 FF", 4);

	DWORD oldProtect;
	VirtualProtect(p_fReach, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect);
	float oldReach = pThis->fields.maxDistance;
	pThis->fields.maxDistance = F::fReachDist;
	*p_fReach = F::fReachDist;

	oPunch(pThis, pMethod);

	if (F::bFastPunch)
		pThis->fields.ready = true;

	pThis->fields.maxDistance = oldReach;
	*p_fReach = oldReach;
	
	VirtualProtect(p_fReach, sizeof(float), oldProtect, nullptr);
}
