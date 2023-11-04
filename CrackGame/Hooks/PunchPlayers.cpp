#include "pch.h"

void __stdcall Hook::PunchPlayers::hkPunch(PunchPlayers_o* pThis, const MethodInfo* pMethod) {
	static auto oPunch = static_cast<decltype(&hkPunch)>(pPunch);

	float oldReach = pThis->fields.maxDistance;
	pThis->fields.maxDistance = F::fReachDist;

	oPunch(pThis, pMethod);

	pThis->fields.maxDistance = oldReach;
}
