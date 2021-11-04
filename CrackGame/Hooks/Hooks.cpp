#include "pch.h"

INL bool Hook::Init()
{
	if (MH_Initialize() != MH_OK)
		return false;

	// TODO:
	// Add reach for punching (Somewhat done???)

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
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 50 80 79 40 00"),
			PlayerMovement, Update);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 8B C4 48 89 58 20 55 48 8D 68 B8"),
			PlayerMovement, Movement);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 81 EC ? ? ? ? 33 D2 48 8B D9"),
			OnlinePlayerMovement, Update);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 48 8B D9 48 85 C9 74 71"),
			AntiCheat, CheatingDetected);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 56 48 83 EC 50 80 3D ? ? ? ? ? 0F B6 F2"),
			GamemodeLights, ToggleLights);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9 0F 29 74 24 ? 0F 28 F1 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05"),
			GamemodeRedLight, RedLight);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9 0F 29 74 24 ? 0F 28 F1 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05"),
			GamemodeRedLight, GreenLight);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 60 80 3D ? ? ? ? ? 49 8B F0 48 8B DA 48 8B F9 75 73"),
			GamemodeBombTag, TagPlayer);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 4C 89 74 24 ? 55 48 8B EC 48 83 EC ? 80 3D ? ? ? ? ? 4D 8B F1"),
			PlayerStatus, DamagePlayer);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B F9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 89 5C 24"),
			LobbyManager, StartLobby);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 80 3D ? ? ? ? ? 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05"),
			GameManager, GetPlayersAlive);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4C 8B F2 48 8B F1 80 3D ? ? ? ? ? 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 33 FF 48 8B 0D"),
			ClientSend, PlayerPosition);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F 29 74 24 ? 0F 29 7C 24 ? 49 8B F0"),
			ClientSend, PlayerRotation);
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	return true;
}

INL bool Hook::Shutdown()
{
	return MH_Uninitialize();
}