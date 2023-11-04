#pragma once

namespace Hook
{
	namespace PlayerInventory
	{
		inline void* pRemoveItem;
		void __stdcall hkRemoveItem(PlayerInventory_o* pThis, int objectID, const MethodInfo* pMethod);
	}
}