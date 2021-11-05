#include "pch.h"

void __stdcall Hook::PlayerStatus::hkDamagePlayer(PlayerStatus_o* pThis, int32_t dmg, UnityEngine_Vector3_o* damageDir, uint64_t damageDoerId, int32_t itemId, const MethodInfo* pMethod)
{
	static auto oDamagePlayer = static_cast<decltype(&hkDamagePlayer)>(pDamagePlayer);

	if (!F::bGodmode)
		oDamagePlayer(pThis, dmg, damageDir, damageDoerId, itemId, pMethod);
}
