#include "pch.h"

#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))


void __stdcall Hook::PunchPlayers::hkPunch(PunchPlayers_o* pThis, const MethodInfo* pMethod)
{
	static auto oPunch = static_cast<decltype(&hkPunch)>(pPunch);

	static float* pReachAccessPoint = (float*)MEM::PatternScanRel("GameAssembly.dll", "F3 0F 10 15 ? ? ? ? 48 8D 55 FF", 4);

	oPunch(pThis, pMethod);

	pThis->fields.ready = true;

	return;
}
