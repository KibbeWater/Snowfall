#include "pch.h"

void __stdcall Hook::PlayerInput::hkUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod)
{
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);

	oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerInput::hkFixedUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod)
{
	static auto oFixedUpdate = static_cast<decltype(&hkFixedUpdate)>(pFixedUpdate);

	/*auto oldFreeze = GameAPI::GetPersistentData()->static_fields->frozen;
	if (F::bDisablePregameFreeze)
		GameAPI::GetPersistentData()->static_fields->frozen = false;
	if (F::bFly)
		GameAPI::GetPersistentData()->static_fields->frozen = true;*/

	oFixedUpdate(pThis, pMethod);

	/*GameAPI::GetPersistentData()->static_fields->frozen = oldFreeze;*/
}
