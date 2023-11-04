#pragma once

namespace Hook {
	namespace ItemSnowball {
		inline void* pTryUse;
		void __stdcall hkTryUse(ItemSnowball_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod);
	}
}