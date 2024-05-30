#include "pch.h"

void __stdcall Hook::ClientHandle::hkTagPlayer(Packet_o* packet, const MethodInfo* pMethod) {
	static auto oTagPlayer = static_cast<decltype(&hkTagPlayer)>(pTagPlayer);

	oTagPlayer(packet, pMethod);

	if (GameAPI::GetGamemode() == MODE_TAG) {
		auto tagger = PacketUtil::ReadLong(packet);
		auto tagged = PacketUtil::ReadLong(packet);
		PacketUtil::ResetPacket(packet);

		auto rot = new Vector3(1, 1, 1);
		static long yourSteamID = GameAPI::GetSteamID();
		if (tagged == yourSteamID && F::bAntiBombTag && tagger != yourSteamID && tagger != 0)
			GameAPI::DamagePlayer(tagger, 0, rot->ToEngine(), WEAPON_STICK, GameAPI::GetItemByID(WEAPON_STICK)->fields.objectID);
	}
}

void __stdcall Hook::ClientHandle::hkPlayerPosition(Packet_o* packet, const MethodInfo* pMethod) {
	static auto oPlayerPosition = static_cast<decltype(&hkPlayerPosition)>(pPlayerPosition);

	// In future versions, we can just read from the packet and re-write to it ourselves
	auto packetWrapper = new Packet(packet);
	auto shouldBlock = G::oCallbackManager->trigger_event(Callbacks::Event::HandleMove, packetWrapper);

	if (!shouldBlock)
		oPlayerPosition(packet, pMethod);
}
