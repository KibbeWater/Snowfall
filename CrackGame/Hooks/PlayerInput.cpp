#include "pch.h"

void __stdcall Hook::PlayerInput::hkUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod) {
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);
	
	return oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerInput::hkFixedUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod) {
	static auto oFixedUpdate = static_cast<decltype(&hkFixedUpdate)>(pFixedUpdate);
	static auto fnMovement = reinterpret_cast<void(__thiscall*)(PlayerMovement_o*, float, float, const MethodInfo*)>(GameAPI::FindMethod("Movement", 2)->m_pMethodPointer);

	if (Config::get("gamemode_nofreeze", false)) {
		GameAPI::GetPersistentData()->static_fields->frozen = false;
		GameAPI::GetPersistentData()->static_fields->hnsFrozen = false;
	}

	oFixedUpdate(pThis, pMethod);

	if (Config::get("combat_autofire", false) && GetAsyncKeyState(0x01) & 0x8000) {
		GameAPI::UseItem();
	}

	if (Config::get("misc_chatspammer_on", false))
		GameAPI::SendChatMessage(Config::get("misc_chatspammer_msg", std::string("Snowfall on top")));
}
