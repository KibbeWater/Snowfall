#include "pch.h"

void __stdcall Hook::GameManager::hkGetPlayersAlive(GameManager_o* pThis, const MethodInfo* pMethod)
{
	static auto oGetPlayersAlive = static_cast<decltype(&hkGetPlayersAlive)>(pGetPlayersAlive);

	G::pGameManager = pThis;

	oGetPlayersAlive(pThis, pMethod);
}
