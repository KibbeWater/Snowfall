#include "pch.h"

void __stdcall Hook::OnlinePlayerMovement::hkUpdate(OnlinePlayerMovement_o* pThis, const MethodInfo* pMethod)
{
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);

	M::pPlayerManager = pThis->fields._playerManager_k__BackingField;

	oUpdate(pThis, pMethod);
}
