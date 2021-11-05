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
