#include "pch.h"

INL bool Hook::Init() {
	if (MH_Initialize() != MH_OK)
		return false;

	// TODO:
	// Add reach for punching (Somewhat done???)
	// Fix another pattern for StealHat, causes some kind of overflow due to long pattern'
	// Make cheat for color gamemode
	// Features to fix: Click TP

	// Do hooks
	{
		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 80 7B ? ? 74 ? F3 0F 10 15 ? ? ? ? 45 33 C9 C6 43 ? ? 48 8B CB 48 8B 15 ? ? ? ? E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 09 48 85 C9 74 ? 33 D2 E8 ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? F3 0F 10 15 ? ? ? ? 45 33 C9 0F 57 C9"), 
			PunchPlayers, Punch);*/
		DO_HOOK(reinterpret_cast<PVOID>(GameAPI::FindMethod("PushPlayer")->m_pMethodPointer),
			PlayerMovement, PushPlayer);
		DO_HOOK(reinterpret_cast<PVOID>(GameAPI::FindMethod("Jump", 0)->m_pMethodPointer),
			PlayerMovement, Jump);
		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 50 80 79 40 00"),
			PlayerMovement, Update);*/
		DO_HOOK(reinterpret_cast<PVOID>(GameAPI::FindMethod("Movement", 2)->m_pMethodPointer),
			PlayerMovement, Movement);
		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 37 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 80 7B 30 00"),
			PlayerInput, Update);*/
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer("PlayerInput", "FixedUpdate")),
			PlayerInput, FixedUpdate);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(GameAPI::FindMethod("GetHpRatio", 0)->m_pClass, "DamagePlayer")),
			PlayerStatus, DamagePlayer);

		auto cPlayerInventory = GameAPI::FindMethod("LockInventory", 1)->m_pClass;
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cPlayerInventory, "RemoveItem")),
			PlayerInventory, RemoveItem);

		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 81 EC ? ? ? ? 33 D2 48 8B D9"),
			OnlinePlayerMovement, Update);*/
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 48 8B D9 48 85 C9 74 71"),
			AntiCheat, CheatingDetected);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(GameAPI::FindMethod("Strobe", 0)->m_pClass, "ToggleLights")),
			GamemodeLights, ToggleLights);

		auto cGamemodeRedLight = GameAPI::FindMethod("CheckMovement", 0)->m_pClass;
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cGamemodeRedLight, "RedLight")),
			GamemodeRedLight, RedLight);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cGamemodeRedLight, "GreenLight")),
			GamemodeRedLight, GreenLight);
		/*DO_HOOK(reinterpret_cast<PVOID>(MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 14 39 B9 ? ? ? ? 75 0C E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 81 ? ? ? ? 48 8B 40 10 48 85 C0 0F 84 ? ? ? ? 48 8B 40 50 48 85 C0 0F 84 ? ? ? ? 83 78 18 0F", 1)),
			GamemodeBombTag, TagPlayer);
		DO_HOOK(reinterpret_cast<PVOID>(GameAPI::FindMethod("StealHat", 2)->m_pMethodPointer),
			GamemodeHat, StealHat);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(GameAPI::FindClassByField("taggedPlayers", "TryTagPlayer"), "TryTagPlayer")),
			GamemodeTag, TagPlayer);*/

		DO_HOOK(reinterpret_cast<PVOID>(GameAPI::FindMethod("SendMessage", 1)->m_pMethodPointer),
			Chatbox, SendMsg);
		
		auto cLobbyManager = GameAPI::FindMethod("AddPlayerToLobby", 1)->m_pClass;
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cLobbyManager, "StartLobby")),
			LobbyManager, StartLobby);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cLobbyManager, "BanPlayer")),
			LobbyManager, BanPlayer);

		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 80 3D ? ? ? ? ? 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05"),
			GameManager, GetPlayersAlive);*/
		
		auto cClientSend = GameAPI::FindMethod("SendSpectating", 1)->m_pClass;
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "PlayerPosition"),
			ClientSend, PlayerPosition);
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "PlayerRotation"),
			ClientSend, PlayerRotation);
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "UseItem"),
			ClientSend, UseItem);
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "SendChatMessage"),
			ClientSend, SendChatMessage);

		auto cClientHandle = GameAPI::FindMethod("BlockCrush", 1)->m_pClass;
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cClientHandle, "TagPlayer")),
			ClientHandle, TagPlayer);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cClientHandle, "PlayerPosition")),
			ClientHandle, PlayerPosition);

		auto cGlassBreak = GameAPI::FindMethod("MakeSolid", 0)->m_pClass;
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cGlassBreak, "OnTriggerEnter"),
			GlassBreak, OnTriggerEnter);

		auto cItemGun = GameAPI::FindMethod("GetHit", 1)->m_pClass;
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cItemGun, "TryUse"),
			ItemGun, TryUse);
		
		Unity::il2cppClass* cItemMelee = GameAPI::FindClassByField("hitFx", "TryUse");
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cItemMelee, "TryUse"),
			ItemMelee, TryUse);

		Unity::il2cppClass* cItemSnowball = GameAPI::FindClassByField("throwPrefab", "TryUse");
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cItemSnowball, "TryUse"),
			ItemSnowball, TryUse);

		DO_HOOK(reinterpret_cast<PVOID>(GameAPI::FindMethod("AddRecoil", 1)->m_pMethodPointer),
			CameraRecoil, AddRecoil);

		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 80 7B 20 00 75 4D F3 0F 10 15 ? ? ? ? 45 33 C9 C6 43 20 01 48 8B CB 48 8B 15 ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 8B 5B 18 F6 81 ? ? ? ? ? 74 0E 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 D2 8B CB 48 83 C4 20 5B E9 ? ? ? ? 48 83 C4 20 5B C3 CC CC CC CC CC CC C6 41 20 01"),
			SnowballPileInteract, TryInteract);

		std::vector<Unity::il2cppClass*> m_vClasses;
		IL2CPP::Class::FetchClasses(&m_vClasses, "Assembly-CSharp-firstpass", "SteamworksNative");
		for (size_t i = 0; i < m_vClasses.size(); i++) {
			auto m_vClass = m_vClasses.at(i);
			if (strcmp("SteamMatchmaking", m_vClass->m_pName) == 0) {
				DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(m_vClass, "GetNumLobbyMembers"),
					SteamMatchmaking, GetNumLobbyMembers);
				DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(m_vClass, "SetLobbyData"),
					SteamMatchmaking, SetLobbyData);
			}
		}
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	return true;
}

INL bool Hook::Shutdown()
{
	return MH_Uninitialize();
}