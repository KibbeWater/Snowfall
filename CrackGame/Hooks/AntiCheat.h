#pragma once

namespace Hook
{
	namespace AntiCheat
	{
		inline void* pCheatingDetected;
		void __stdcall hkCheatingDetected(CodeStage_AntiCheat_Detectors_ACTkDetectorBase_WallHackDetector__o* pThis, const MethodInfo_441F40* pMethod);
	}
}