#pragma once

namespace Hook
{
	namespace PlayerInput
	{
		inline void* pUpdate;
		void __stdcall hkUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod);
	}
}