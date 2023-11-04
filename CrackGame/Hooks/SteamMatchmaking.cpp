#include "pch.h"

int __stdcall Hook::SteamMatchmaking::hkGetNumLobbyMembers(SteamworksNative_CSteamID_o steamIDLobby, const MethodInfo* method) {
	static auto oGetNumLobbyMembers = static_cast<decltype(&hkGetNumLobbyMembers)>(pGetNumLobbyMembers);

	/* if (F::bFakePlayers)
		return F::iFakePlayers; */

	return oGetNumLobbyMembers(steamIDLobby, method);
}

bool __stdcall Hook::SteamMatchmaking::hkSetLobbyData(SteamworksNative_CSteamID_o steamIDLobby, System_String_o* pchKey, System_String_o* pchValue, const MethodInfo* method) {
	static auto oSetLobbyData = static_cast<decltype(&hkSetLobbyData)>(pSetLobbyData);

	auto key = reinterpret_cast<Unity::System_String*>(pchKey);
	auto value = reinterpret_cast<Unity::System_String*>(pchValue);

	if (F::bFakePlayers && key->ToString().find("PlayersIn") != std::string::npos) {
		auto newVal = IL2CPP::String::New(to_string(F::iFakePlayers));
		value = newVal;
		pchValue = reinterpret_cast<System_String_o*>(&newVal);
	}

	ofstream file("SetLobbyData.txt", std::ios::app);
	file << key->ToString() << " = " << value->ToString() << std::endl;
	file.close();

	return oSetLobbyData(steamIDLobby, pchKey, pchValue, method);
}
