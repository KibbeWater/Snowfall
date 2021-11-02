#pragma once

namespace Hook {
	namespace OnlinePlayerMovement {
		inline void* pUpdate;
		void __stdcall hkUpdate(OnlinePlayerMovement_o* pThis, const MethodInfo* pMethod);
	}
}