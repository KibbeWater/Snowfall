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

	inline CommandHandler *commandHandler = new CommandHandler();
}

namespace F
{
	// General
	inline bool bDisabledCamShake = false;
	inline bool bDisablePregameFreeze = false;
	inline bool bLagSwitch = false;
	inline bool bAutoClicker = false;
	inline bool bCommandHandler = false;

	// Combat
	inline bool bGodmode = false;
	inline bool bFastSwing = false;
	inline bool bAutoSnowballRefill = false;
	inline bool bFastThrow = false;
	inline bool bInfAmmo = false;
	inline bool bRapidFire = false;
	inline bool bNoRecoil = false;
	inline bool bReach = false;
	inline float fReachDist = 2.5;

	// Movement
	inline bool bSpeedhack = false;
	inline int iSpeedPercent = 100;
	inline bool bAirJump = false;
	inline bool bAntiKnockback = false;
	inline bool bAdvancedAntiKB = false;
	inline bool bNoSlide = false;

	// Gamemodes
	inline bool bRedGreenProtection = false;
	inline bool bAntiBombTag = false;
	inline bool bLightsAlwaysOn = false;
	inline bool bPreventGlassBreak = false;

	// Item giver
	inline int iWeaponID = 0;

	// Lobby
	inline bool bMaxPlayersOverride = false;
	inline bool bHackerPrevention = false;
	inline int iMaxPlayersCount = 40;
	inline bool bFakePlayers = false;
	inline int iFakePlayers = 0;

	// Other
	inline bool bClickTP = false;
	inline bool bFly = false;
	inline bool bBlockItemRemoval = false;
	inline bool bDebug = false;
	inline bool bCrasher = false;
	inline bool bFlingAll = false;
	inline bool bChatSpammer = false;
	inline char sSpammerMsg[32767] = {"LOL"};
}