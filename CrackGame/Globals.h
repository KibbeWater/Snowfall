#pragma once

struct GameManager_o;
struct PlayerManager_o;

namespace M
{
	inline GameManager_o *pGameManager = nullptr;
	inline PlayerManager_o *pPlayerManager = nullptr;
	inline SnowballPileInteract_o *pSnowballPileInteract = nullptr;
}

namespace G
{
	inline bool bRedLightFreeze = false;
	inline bool bAnticheatDisabler = true;
	inline float fKillHeight = -100.0;

	inline Vector3 lastSentPosition = Vector3(0, 0, 0);

	inline Callbacks *oCallbackManager = new Callbacks();
	inline std::vector<Vector3 *> vPositionOverrideQueue = {};
	inline sol::state *vLuaState = new sol::state();

	inline ImDrawList *pDrawList = nullptr;

	inline CommandHandler *commandHandler = new CommandHandler();

	inline ID3D11Device* g_pd3dDevice = nullptr;
}

namespace F
{

}