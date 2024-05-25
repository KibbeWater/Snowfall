#pragma once
class Lobby {
public:
	static bool IsLobbyOwner();
	static void GiveWeapon(EWeapons weapon, long client);
	static void GiveAllWeapon(EWeapons weapon);
};
