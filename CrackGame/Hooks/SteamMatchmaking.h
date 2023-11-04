#pragma once

namespace Hook {
	namespace SteamMatchmaking {
		inline void* pGetNumLobbyMembers;
		int __stdcall hkGetNumLobbyMembers(SteamworksNative_CSteamID_o steamIDLobby, const MethodInfo* method);

		inline void* pSetLobbyData;
		bool __stdcall hkSetLobbyData(SteamworksNative_CSteamID_o steamIDLobby, System_String_o* pchKey, System_String_o* pchValue, const MethodInfo* method);
	}
}