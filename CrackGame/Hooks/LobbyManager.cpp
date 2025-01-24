#include "pch.h"

void __stdcall Hook::LobbyManager::hkStartLobby(LobbyManager_o* pThis, const MethodInfo* pMethod)
{
	static auto oStartLobby = static_cast<decltype(&hkStartLobby)>(pStartLobby);

	//Provide override settings
	if (Config::get("lobby_maxplayers_on", false))
		pThis->fields.gameSettings->fields.maxPlayers = Config::get("lobby_maxplayers_count", 40);

	//Call original function
	oStartLobby(pThis, pMethod);
}

void __stdcall Hook::LobbyManager::hkBanPlayer(LobbyManager_o* pThis, long ID, const MethodInfo* pMethod)
{
	static auto oBanPlayer = static_cast<decltype(&hkBanPlayer)>(pBanPlayer);

	static long myID = GameAPI::GetSteamID();
	if (G::bAnticheatDisabler && myID == ID)
		return;
	
	oBanPlayer(pThis, ID, pMethod);
}
