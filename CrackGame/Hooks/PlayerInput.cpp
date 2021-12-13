#include "pch.h"

void __stdcall Hook::PlayerInput::hkUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod) {
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);
	static auto fnLook = reinterpret_cast<void(__thiscall*)(PlayerInput_o*, const MethodInfo*)>(IL2CPP::Class::Utils::GetMethodPointer("PlayerInput", "Look", 0));
	static auto fnAlwaysInput = reinterpret_cast<void(__thiscall*)(PlayerInput_o*, const MethodInfo*)>(IL2CPP::Class::Utils::GetMethodPointer("PlayerInput", "AlwaysInput", 0));
	static auto fnNotFrozenInput = reinterpret_cast<void(__thiscall*)(PlayerInput_o*, const MethodInfo*)>(IL2CPP::Class::Utils::GetMethodPointer("PlayerInput", "NotFrozenInput", 0));

	if (!F::bDisablePregameFreeze)
		return oUpdate(pThis, pMethod);

	fnAlwaysInput(pThis, nullptr);
	fnLook(pThis, nullptr);
	fnNotFrozenInput(pThis, nullptr);
}

void __stdcall Hook::PlayerInput::hkFixedUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod) {
	static auto oFixedUpdate = static_cast<decltype(&hkFixedUpdate)>(pFixedUpdate);
	static auto fnMovement = reinterpret_cast<void(__thiscall*)(PlayerMovement_o*, float, float, const MethodInfo*)>(GameAPI::FindMethod("Movement", 2)->m_pMethodPointer);

	if (!F::bDisablePregameFreeze)
		return oFixedUpdate(pThis, pMethod);

	if (pThis->fields.playerMovement)
		return fnMovement(pThis->fields.playerMovement, pThis->fields.x, pThis->fields.y, nullptr);
}
