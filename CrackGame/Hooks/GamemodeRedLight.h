#pragma once

namespace Hook {
	namespace GamemodeRedLight {
		inline void* pRedLight;
		void __stdcall hkRedLight(GameModeRedLight_o* pThis, float reactionTime, const MethodInfo* pMethod);

		inline void* pGreenLight;
		void __stdcall hkGreenLight(GameModeRedLight_o* pThis, float reactionTime, const MethodInfo* pMethod);
	}
}