#pragma once

namespace Hook
{
	namespace PlayerInventory
	{
		inline void* pUseAmmo;
		void __stdcall hkUseAmmo(PlayerInventory_o* pThis, int type, int ammoNeeded, const MethodInfo* pMethod);
	}
}