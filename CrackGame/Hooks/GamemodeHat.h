#pragma once

namespace Hook
{
	namespace GamemodeHat
	{
		inline void* pStealHat;
		void __stdcall hkStealHat(GameModeHat_o* pThis, long stealer, long stolenFrom, const MethodInfo* pMethod);
	}
}