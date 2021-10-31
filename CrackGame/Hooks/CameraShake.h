#pragma once

namespace Hook
{
	namespace CameraShake
	{
		inline void* pShake;
		MilkShake_ShakeInstance_o* __stdcall hkShake(MilkShake_Shaker_o* pThis, MilkShake_IShakeParameters_o* shakeData, System_Nullable_int__o seed, const MethodInfo* pMethod);
	}
}