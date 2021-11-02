#pragma once

namespace Hook
{
	namespace PlayerMovement
	{
		inline void* pPushPlayer;
		void __stdcall hkPushPlayer(PlayerMovement_o* pThis, UnityEngine_Vector3_o pushForce, const MethodInfo* pMethod);

		inline void* pJump;
		void __stdcall hkJump(PlayerMovement_o* pThis, const MethodInfo* pMethod);

		inline void* pUpdate;
		void __stdcall hkUpdate(PlayerMovement_o* pThis, const MethodInfo* pMethod);

		inline void* pMovement;
		void __stdcall hkMovement(PlayerMovement_o* pThis, float x, float y, const MethodInfo* pMethod);
	}
}