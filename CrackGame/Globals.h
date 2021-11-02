#pragma once

struct GameManager_o;
struct PlayerManager_o;

namespace Globals {
	inline bool bRedLightFreeze = false;

	inline GameManager_o* ptrGameManager = nullptr;
	inline PlayerManager_o* ptrPlayerManager = nullptr;

	namespace Temp { //Temporary solution to hardcoding
		inline int32 iMaxPlayers = 1337;
	}
}