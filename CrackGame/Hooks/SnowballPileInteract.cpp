#include "pch.h"

void __stdcall Hook::SnowballPileInteract::hkTryInteract(SnowballPileInteract_o* pThis, const MethodInfo* pMethod) {
	static auto oTryInteract = static_cast<decltype(&hkTryInteract)>(pTryInteract);

	M::pSnowballPileInteract = pThis;

	if (Config::get("combat_fastthrow", false))
		pThis->fields.ready = false;

	oTryInteract(pThis, pMethod);
}
