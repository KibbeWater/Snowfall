#pragma once

namespace Hook
{
	namespace GamemodeTag
	{
		inline void* pTagPlayer;
		void __stdcall hkTagPlayer(GameModeTag_o* pThis, long tagger, long tagged, const MethodInfo* pMethod);
	}
}