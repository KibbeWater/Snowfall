#include "pch.h"

void __stdcall Hook::PlayerInventory::hkRemoveItem(PlayerInventory_o* pThis, int objectID, const MethodInfo* pMethod) {
	static auto oRemoveItem = static_cast<decltype(&hkRemoveItem)>(pRemoveItem);

	if (!F::bBlockItemRemoval)
		oRemoveItem(pThis, objectID, pMethod);
}
