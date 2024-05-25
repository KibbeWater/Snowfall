#pragma once

class Engine {
public:
	static void Teleport(Vector3 position);
	static long GetSteamID();
	static std::vector<PlayerManager> GetPlayers();
	static LocalPlayer GetLocalPlayer();
};
