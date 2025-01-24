#include "pch.h"

void __stdcall Hook::ItemMelee::hkTryUse(ItemMelee_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod)
{
	static auto oTryUse = static_cast<decltype(&hkTryUse)>(pTryUse);

	if (Config::get("combat_fastswing", false))
		pThis->fields.ready = true;

	oTryUse(pThis, camForward, pMethod);
}
