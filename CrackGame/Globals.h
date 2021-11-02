#pragma once

struct GameManager_o;
struct PlayerManager_o;

namespace G 
{
	inline bool bRedLightFreeze = false;

	inline GameManager_o* pGameManager = nullptr;
	inline PlayerManager_o* pPlayerManager = nullptr;

	namespace Temp { // Temporary solution to hardcoding
		inline int32 iMaxPlayers = 1337;
	}
}