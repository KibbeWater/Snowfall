#include "pch.h"

void __stdcall Hook::PunchPlayers::hkPunch(PunchPlayers_o* pThis, const MethodInfo* pMethod)
{
	static auto oPunch = static_cast<decltype(&hkPunch)>(pPunch);

	pThis->fields.ready = true;

	return oPunch(pThis, pMethod);
}
