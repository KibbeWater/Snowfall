#include "pch.h"

void __stdcall Hook::PlayerInput::hkUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod)
{
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);

	*reinterpret_cast<bool*>(GameAPI::GetPersistentData() + 0xB8) = false;

	oUpdate(pThis, pMethod);
}
