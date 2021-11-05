#include "pch.h"

void __stdcall Hook::PlayerInventory::hkUseAmmo(PlayerInventory_o* pThis, int type, int ammoNeeded, const MethodInfo* pMethod)
{
	static auto oUseAmmo = static_cast<decltype(&hkUseAmmo)>(pUseAmmo);

	oUseAmmo(pThis, type, ammoNeeded, pMethod);
}
