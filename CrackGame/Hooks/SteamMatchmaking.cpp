#include "pch.h"

int __stdcall Hook::SteamMatchmaking::hkGetNumLobbyMembers(SteamworksNative_CSteamID_o steamIDLobby, const MethodInfo* method) {
	static auto oGetNumLobbyMembers = static_cast<decltype(&hkGetNumLobbyMembers)>(pGetNumLobbyMembers);

	/* if (F::bFakePlayers)
		return F::iFakePlayers; */

	return oGetNumLobbyMembers(steamIDLobby, method);
}

bool __stdcall Hook::SteamMatchmaking::hkSetLobbyData(SteamworksNative_CSteamID_o steamIDLobby, System_String_o* pchKey, System_String_o* pchValue, const MethodInfo* method) {
	static auto oSetLobbyData = static_cast<decltype(&hkSetLobbyData)>(pSetLobbyData);

	return oSetLobbyData(steamIDLobby, pchKey, pchValue, method);
}
