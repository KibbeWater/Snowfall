#pragma once

namespace Hook
{
	namespace GamemodeHat
	{
		inline void* pStealHat;
		void __stdcall hkStealHat(GameModeHat_o* pThis, uint64_t stealer, uint64_t stolenFrom, const MethodInfo* pMethod);
	}
}