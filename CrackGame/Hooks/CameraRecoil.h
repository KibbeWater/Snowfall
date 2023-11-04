#pragma once

namespace Hook {
	namespace CameraRecoil {
		inline void* pAddRecoil;
		void __stdcall hkAddRecoil(UnityEngine_Vector2_o recoil, const MethodInfo* pMethod);
	}
}