#pragma once

namespace Hook
{
	namespace ClientSend
	{
		inline void* pPlayerPosition;
		void __stdcall hkPlayerPosition(UnityEngine_Vector3_o* position, uint64_t toId, const MethodInfo* pMethod);

		inline void* pPlayerRotation;
		void __stdcall hkPlayerRotation(float x, float y, uint64_t toId, const MethodInfo* pMethod);

		inline void* pDamagePlayer;
		void __stdcall hkDamagePlayer(long hurtPlayerId, int damage, UnityEngine_Vector3_o* damageDir, int itemID, int objectID, const MethodInfo* pMethod);

		inline void* pUseItem;
		void __stdcall hkUseItem(int itemID, UnityEngine_Vector3_o* dir, const MethodInfo* pMethod);

		HOOK_DEF(SendChatMessage, void, System_String_o* message)
	}
}