#include "pch.h"

MilkShake_ShakeInstance_o* __stdcall Hook::CameraShake::hkShake(MilkShake_Shaker_o* pThis, MilkShake_IShakeParameters_o* shakeData, System_Nullable_int__o seed, const MethodInfo* pMethod)
{
	static auto oShake = static_cast<decltype(&hkShake)>(pShake);

	if (F::bDisabledCamShake) {
		MilkShake_ShakeInstance_o shakeInstance = {};
		return &shakeInstance;
	}

	return oShake(pThis, shakeData, seed, pMethod);
}
