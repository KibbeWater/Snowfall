#pragma once

namespace Hook
{
	namespace GameManager
	{
		inline void* pGetPlayersAlive;
		void __stdcall hkGetPlayersAlive(GameManager_o* pThis, const MethodInfo* pMethod);
	}
}