#include "pch.h"

void __stdcall Hook::ItemSnowball::hkTryUse(ItemSnowball_o* pThis, UnityEngine_Transform_o* camForward, const MethodInfo* pMethod) {
	static auto oTryUse = static_cast<decltype(&hkTryUse)>(pTryUse);

	if (F::bFastThrow)
		pThis->fields.ready = true;

	oTryUse(pThis, camForward, pMethod);

	if (F::bAutoSnowballRefill)
		GameAPI::TrySnowballReload();
}
