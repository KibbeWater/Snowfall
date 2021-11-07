#pragma once

namespace Hook
{
	namespace ItemMelee
	{
		inline void* pTryUse;
		void __stdcall hkTryUse(ItemMelee_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod);
	}
}