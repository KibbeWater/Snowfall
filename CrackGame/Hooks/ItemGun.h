#pragma once

namespace Hook {
	namespace ItemGun {
		inline void* pTryUse;
		void __stdcall hkTryUse(ItemGun_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod);
	}
}