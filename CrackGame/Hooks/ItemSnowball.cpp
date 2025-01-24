#include "pch.h"

void __stdcall Hook::ItemSnowball::hkTryUse(ItemSnowball_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod) {
	static auto oTryUse = static_cast<decltype(&hkTryUse)>(pTryUse);

	if (Config::get("combat_fastthrow", false))
		pThis->fields.ready = true;

	oTryUse(pThis, camForward, pMethod);

	if (Config::get("combat_autosnowball_enabled", false))
		GameAPI::TrySnowballReload();
}
