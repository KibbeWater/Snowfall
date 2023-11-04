#include "pch.h"

void __stdcall Hook::PlayerInput::hkUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod) {
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);
	
	return oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerInput::hkFixedUpdate(PlayerInput_o* pThis, const MethodInfo* pMethod) {
	static auto oFixedUpdate = static_cast<decltype(&hkFixedUpdate)>(pFixedUpdate);
	static auto fnMovement = reinterpret_cast<void(__thiscall*)(PlayerMovement_o*, float, float, const MethodInfo*)>(GameAPI::FindMethod("Movement", 2)->m_pMethodPointer);

	if (F::bDisablePregameFreeze) {
		GameAPI::GetPersistentData()->static_fields->frozen = false;
		GameAPI::GetPersistentData()->static_fields->hnsFrozen = false;
	}

	oFixedUpdate(pThis, pMethod);

	if (F::bAutoClicker && GetAsyncKeyState(0x01) & 0x8000) {
		GameAPI::UseItem();
	}

	if (F::bCrasher) {
		if (GameAPI::TrySnowballReload())
			GameAPI::DropItem();
	}

	if (F::bChatSpammer)
		GameAPI::SendChatMessage(F::sSpammerMsg);

	if (F::bFlingAll) {
		F::bFlingAll = false;
		std::string m_sObjectSubstring = "OnlinePlayer";

		Unity::il2cppClass* m_pSystemTypeClass = IL2CPP::Class::Find("UnityEngine.GameObject");
		auto m_pSystemType = IL2CPP::Class::GetSystemType(m_pSystemTypeClass);
		auto m_pObjects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(m_pSystemType);

		for (uintptr_t u = 0U; m_pObjects->m_uMaxLength > u; ++u) {
			Unity::CGameObject* m_pObject = m_pObjects->At(u);
			if (!m_pObject) continue; // Just in-case

			// Obtaining object name and then converting it to std::string
			std::string m_sObjectName = m_pObject->GetName()->ToString();
			if (m_sObjectName.find(m_sObjectSubstring) != std::string::npos) {
				auto pos = (new Vector3(m_pObject->GetTransform()->GetPosition()))->ToEngine();
				if (F::bDebug)
					GameAPI::Log("Flinging player at: " + std::to_string(pos.fields.x) + ", " + std::to_string(pos.fields.y) + ", " + std::to_string(pos.fields.z));
				GameAPI::CSendPosition(&pos);
				if (F::bDebug)
					GameAPI::Log("Flung");
				// GameAPI::ForceMovementUpdate();
				//break;
			}
		}
	}
}
