#pragma once

struct GameManager_o;
struct PlayerManager_o;

namespace G {
	inline bool bRedLightFreeze = false;
	inline bool bAnticheatDisabler = false;

	inline GameManager_o* pGameManager = nullptr;
	inline PlayerManager_o* pPlayerManager = nullptr;
}

namespace F {
	//General
	inline bool bDisabledCamShake = false;
	
	//Combat
	inline bool bGodmode = false;
	inline bool bFastPunch = false;
	inline bool bInfAmmo = false;
	inline bool bReach = false;
	inline float fReachDist = 2.5;

	//Movement
	inline bool bSpeedhack = false;
	inline int iSpeedPercent = 100;
	inline bool bAirJump = false;
	inline bool bAntiKnockback = false;
	inline bool bNoSlide = false;

	//Gamemodes
	inline bool bRedGreenProtection = false;
	inline bool bAntiBombTag = false;
	inline bool bLightsAlwaysOn = false;

	//Item giver
	inline int iWeaponID = 0;

	//Lobby
	inline bool bMaxPlayersOverride = false;
	inline int iMaxPlayersCount = 40;
}