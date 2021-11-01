#pragma once

namespace Hook
{
	namespace GamemodeLights
	{
		inline void* pToggleLights;
		void __stdcall hkToggleLights(GameModeLights_o* pThis, bool b, const MethodInfo* pMethod);
	}
}