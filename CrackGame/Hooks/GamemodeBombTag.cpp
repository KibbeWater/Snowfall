#include "pch.h"

void __stdcall Hook::GamemodeBombTag::hkTagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged, const MethodInfo* pMethod)
{
	static auto oTagPlayer = static_cast<decltype(&hkTagPlayer)>(pTagPlayer);

	oTagPlayer(pThis, tagger, tagged, pMethod);

	auto rot = new Vector3(1, 1, 1);
	static long yourSteamID = GameAPI::GetSteamID();
	if (tagged == yourSteamID && F::bAntiBombTag && tagger != yourSteamID && tagger != 0)
		GameAPI::DamagePlayer(tagger, 0, rot->ToEngine(), WEAPON_BOMB, GameAPI::FindItemById(WEAPON_BOMB)->fields.objectID);
}
