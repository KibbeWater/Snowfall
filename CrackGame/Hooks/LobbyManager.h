#pragma once

namespace Hook
{
	namespace LobbyManager
	{
		inline void* pStartLobby;
		void __stdcall hkStartLobby(LobbyManager_o* pThis, const MethodInfo* pMethod);

		inline void* pBanPlayer;
		void __stdcall hkBanPlayer(LobbyManager_o* pThis, long ID, const MethodInfo* pMethod);
	}
}