#pragma once

namespace Hook {
	namespace GlassBreak {
		inline void* pOnTriggerEnter;
		void __stdcall hkOnTriggerEnter(GlassBreak_o* pThis, UnityEngine_Collider_o* collider, const MethodInfo* pMethod);
	}
}