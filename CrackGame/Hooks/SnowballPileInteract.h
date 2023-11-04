#pragma once

namespace Hook {
	namespace SnowballPileInteract {
		inline void* pTryInteract;
		void __stdcall hkTryInteract(SnowballPileInteract_o* pThis, const MethodInfo* pMethod);
	}
}