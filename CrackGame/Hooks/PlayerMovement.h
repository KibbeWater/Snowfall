#pragma once

namespace Hook
{
	namespace PlayerMovement
	{
		inline void* pPushPlayer;
		void __stdcall hkPushPlayer(PlayerMovement_o* pThis, UnityEngine_Vector3_o pushForce, const MethodInfo* pMethod);

		inline void* pJump;
		void __stdcall hkJump(PlayerMovement_o* pThis, const MethodInfo* pMethod);
	}
}