#pragma once

namespace Hook
{
	namespace PlayerStatus
	{
		inline void* pDamagePlayer;
		void __stdcall hkDamagePlayer(PlayerStatus_o* pThis, int32_t dmg, UnityEngine_Vector3_o* damageDir, uint64_t damageDoerId, int32_t itemId, const MethodInfo* pMethod);
	}
}