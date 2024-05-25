#include "pch.h"

void Engine::Teleport(Vector3 position) {
	GameAPI::Teleport(position.ToEngine());
}

long Engine::GetSteamID() {
	return GameAPI::GetSteamID();
}

std::vector<PlayerManager> Engine::GetPlayers() {
	auto players = GameAPI::GetPlayers();
	auto playerManagers = std::vector<PlayerManager>();

	for (auto player : players) {
		playerManagers.push_back(PlayerManager(player));
	}

	return playerManagers;
}

LocalPlayer Engine::GetLocalPlayer() {
	auto players = GameAPI::GetPlayers();
	for (auto player : players) {
		if (player->fields.steamProfile.fields.m_SteamID == GameAPI::GetSteamID()) {
			return LocalPlayer(player);
		}
	}
	return nullptr;
}
