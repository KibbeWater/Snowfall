#include "pch.h"

INL bool Hook::Init()
{
	if (MH_Initialize() != MH_OK)
		return false;

	// Do methods
	{
		
	}

	// Do hooks
	{
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 80 7B ? ? 74 ? F3 0F 10 53"), 
			PunchPlayers, Punch);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B D8 48 8B EA 48 8B F1 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? E8"), 
			CameraShake, Shake);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B F2 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 7B"),
			PlayerMovement, PushPlayer);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 3D ? ? ? ? ? 48 8B D9 75 37"),
			PlayerMovement, Jump);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 48 8B D9 48 85 C9 74 71"),
			AntiCheat, CheatingDetected);
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	return true;
}

INL bool Hook::Shutdown()
{
	return MH_Uninitialize();
}