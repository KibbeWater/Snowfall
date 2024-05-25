#pragma once

enum ESurfaceType
{
	SURFACE_NORMAL,
	SURFACE_ICE,
	SURFACE_FASE_ICE
};

enum ELockState {
	LOCKSTATE_NONE,
	LOCKSTATE_LOCKED,
	LOCKSTATE_CONFINED
};

enum EWeapons {
	WEAPON_RIFLE,
	WEAPON_PISTOL,
	WEAPON_REVOLVER,
	WEAPON_SHOTGUN,
	WEAPON_BAT,
	WEAPON_BOMB,
	WEAPON_KATANA,
	WEAPON_KNIFE,
	WEAPON_PIPE,
	WEAPON_SNOWBALL,
	WEAPON_STICK
};

enum EGameModes {
    MODE_WAITING = 0,
    MODE_RED_LIGHT_GREEN_LIGHT = 1,
    MODE_BASEBALL = 2,
    MODE_STEPPING_STONES = 3,
    MODE_TAG = 4,
    MODE_HIDE_AND_SEEK = 5,
    MODE_BOMB_TAG = 6,
    MODE_LIGHTS_OUT = 7,
    MODE_FALLING_PLATFORMS = 8,
    MODE_KING_OF_THE_HILL = 9,
    MODE_TILE_DRIVE = 10,
    MODE_HAT_KING = 11,
    MODE_RACE = 12,
    MODE_BUSTLING_BUTTONS = 13,
    MODE_PRACTICE = 14,
    MODE_STANDOFF = 15,
    MODE_DEATH_FROM_ABOVE = 16,
    MODE_COLOR_DROP = 17,
    MODE_SNOW_BRAWL = 18,
    MODE_DODGE_BALL = 19,
    MODE_CRAB_FIGHT = 20
};

enum ERenderDistance {
    RENDER_CLOSE = 0,
    RENDER_MEDIUM = 1,
    RENDER_FAR = 2,
    RENDER_ANY = 3
};

// STRUCT DEFS
struct LuaState {
	sol::state* state;
	std::string name;
};
