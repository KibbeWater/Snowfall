#include "pch.h"

void __stdcall Hook::LobbyManager::hkStartLobby(LobbyManager_o* pThis, const MethodInfo* pMethod)
{
	static auto oStartLobby = static_cast<decltype(&hkStartLobby)>(pStartLobby);

	//Provide override settings
	if (F::bMaxPlayersOverride)
		pThis->fields.gameSettings->fields.maxPlayers = F::iMaxPlayersCount;


	//Call original function
	oStartLobby(pThis, pMethod);
}

void __stdcall Hook::LobbyManager::hkBanPlayer(LobbyManager_o* pThis, long ID, const MethodInfo* pMethod)
{
	static auto oBanPlayer = static_cast<decltype(&hkBanPlayer)>(pBanPlayer);

	static long myID = GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.Value;
	if (G::bAnticheatDisabler && myID == ID)
		return;
	
	oBanPlayer(pThis, ID, pMethod);
}
