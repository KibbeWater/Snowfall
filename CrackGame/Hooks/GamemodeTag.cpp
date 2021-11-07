#include "pch.h"

void __stdcall Hook::GamemodeTag::hkTagPlayer(GameModeTag_o* pThis, long tagger, long tagged, const MethodInfo* pMethod)
{
	static auto oTagPlayer = static_cast<decltype(&hkTagPlayer)>(pTagPlayer);

	oTagPlayer(pThis, tagger, tagged, pMethod);

	static long yourSteamID = GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.m_SteamID;
	if (tagged == yourSteamID && F::bAntiBombTag && tagger != yourSteamID && tagger != 0)
		GameAPI::DamagePlayer(tagger, 0, WEAPON_STICK, -1, GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.cameraRot);
}
