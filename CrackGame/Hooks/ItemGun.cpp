#include "pch.h"

void __stdcall Hook::ItemGun::hkTryUse(ItemGun_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod)
{
	static auto oTryUse = static_cast<decltype(&hkTryUse)>(pTryUse);

	if (Config::get("combat_rapidfire_enabled", false))
		pThis->fields.ready = true;

	if (Config::get("combat_infiniteammo", false))
		pThis->fields.itemData->fields.currentAmmo = INT_MAX;

	oTryUse(pThis, camForward, pMethod);
}
