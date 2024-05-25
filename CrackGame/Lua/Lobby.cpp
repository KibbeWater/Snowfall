#include "pch.h"

bool Lobby::IsLobbyOwner() {
	return GameAPI::IsLobbyOwner();
}

void Lobby::GiveWeapon(EWeapons weapon, long client = -1) {
	if (client == -1) {
		auto player = GameAPI::ResolvePlayer64("me");
		GameAPI::LobbyGiveWeapon(player, weapon);
		return;
	}
	GameAPI::LobbyGiveWeapon(client, weapon);
}

void Lobby::GiveAllWeapon(EWeapons weapon) {
	GameAPI::LobbyGiveAllWeapon(weapon);
}
