#include "pch.h"

void __stdcall Hook::ItemGun::hkTryUse(ItemGun_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod)
{
	static auto oTryUse = static_cast<decltype(&hkTryUse)>(pTryUse);

	if (F::bInfAmmo)
		pThis->fields.itemData->fields.currentAmmo = INT_MAX;

	oTryUse(pThis, camForward, pMethod);
}
