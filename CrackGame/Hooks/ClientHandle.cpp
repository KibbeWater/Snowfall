#include "pch.h"

void __stdcall Hook::ClientHandle::hkTagPlayer(Packet_o* packet, const MethodInfo* pMethod) {
	static auto oTagPlayer = static_cast<decltype(&hkTagPlayer)>(pTagPlayer);

	oTagPlayer(packet, pMethod);

	if (GameAPI::GetGamemode() == MODE_TAG) {
		auto tagger = Packet::ReadLong(packet);
		auto tagged = Packet::ReadLong(packet);
		Packet::ResetPacket(packet);

		auto rot = new Vector3(1, 1, 1);
		static long yourSteamID = GameAPI::GetSteamID();
		if (tagged == yourSteamID && F::bAntiBombTag && tagger != yourSteamID && tagger != 0)
			GameAPI::DamagePlayer(tagger, 0, rot->ToEngine(), WEAPON_STICK, GameAPI::GetItemByID(WEAPON_STICK)->fields.objectID);
	}
}