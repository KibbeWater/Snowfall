#include "pch.h"

#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

void __stdcall Hook::PunchPlayers::hkPunch(PunchPlayers_o* pThis, const MethodInfo* pMethod)
{
	static PVOID reachAccessPoint = MEM::PatternScan("GameAssembly.dll", "F3 0F 10 15 ? ? ? ? 48 8D 55 FF");
	BYTE byteAtAP = *(BYTE*)reachAccessPoint;
	int ap = *(reinterpret_cast<int*>(reachAccessPoint) + 4);
	int apLittle = SWAP_INT32(ap);
	static float* reach = reinterpret_cast<float*>(reachAccessPoint) + ap;
	static auto oPunch = static_cast<decltype(&hkPunch)>(pPunch);

	oPunch(pThis, pMethod);

	pThis->fields.ready = true;

	return;
}
