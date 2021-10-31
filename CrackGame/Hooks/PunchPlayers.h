#pragma once

namespace Hook
{
	namespace PunchPlayers
	{
		inline void* pPunch;
		void __stdcall hkPunch(PunchPlayers_o* pThis, const MethodInfo* pMethod);


	}
}