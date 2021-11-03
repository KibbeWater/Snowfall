#pragma once

namespace Hook
{
	namespace GamemodeBombTag
	{
		inline void* pTagPlayer;
		void __stdcall hkTagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged, const MethodInfo* pMethod);
	}
}