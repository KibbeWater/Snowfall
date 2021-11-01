#pragma once

namespace Hook
{
	namespace LobbyManager
	{
		inline void* pStartLobby;
		void __stdcall hkStartLobby(LobbyManager_o* pThis, const MethodInfo* pMethod);
	}
}