#include "pch.h"

INL bool Hook::Init()
{
	if (MH_Initialize() != MH_OK)
		return false;

	// Do hooks
	{
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 0F 29 70 E8 0F 29 78 D8 44 0F 29 40 ? 44 0F 29 48 ? 48"), PunchPlayers, Punch);
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	return true;
}

INL bool Hook::Shutdown()
{
	return MH_Uninitialize();
}