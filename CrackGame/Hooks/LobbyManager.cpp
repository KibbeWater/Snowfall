#include "pch.h"

void __stdcall Hook::LobbyManager::hkStartLobby(LobbyManager_o* pThis, const MethodInfo* pMethod)
{
	static auto oStartLobby = static_cast<decltype(&hkStartLobby)>(pStartLobby);

	//Provide override settings
	pThis->fields.gameSettings->fields.maxPlayers = G::Temp::iMaxPlayers;

	//Call original function
	oStartLobby(pThis, pMethod);
}
