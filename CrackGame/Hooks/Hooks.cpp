#include "pch.h"

INL bool Hook::Init() {
	if (MH_Initialize() != MH_OK)
		return false;

	// TODO:
	// Add reach for punching (Somewhat done???)
	// Fix another pattern for StealHat, causes some kind of overflow due to long pattern'
	// Make cheat for color gamemode
	// Features to fix: AirJump, Click TP

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

		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 60 80 3D ? ? ? ? ? 49 8B F0 48 8B DA 48 8B F9 75 73"),
			GamemodeBombTag, TagPlayer);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B FA 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 0F 29 7C 24 ? 48 85 FF 74 ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 74 ? 45 33 C9 4C 8B C7 B2 ? 48 8B CB E8 ? ? ? ? 45 33 C9 4C 8B C6 33 D2 48 8B CB E8 ? ? ? ? 48 8B 4B ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D6 E8 ? ? ? ? 84 C0 74 ? 48 8B 4B ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D6 E8 ? ? ? ? 48 8B 4B ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 81 ? ? ? ? 48 8B 10 48 85 D2 0F 84 ? ? ? ? 48 3B 7A ? 0F 84 ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 81 ? ? ? ? 48 8B 08 48 85 C9 0F 84 ? ? ? ? 48 3B 71 ? 0F 85 ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 33 D2 EB ? 80 3D ? ? ? ? ? 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? B2 ? 45 33 C0 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D6 E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D6 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 45 33 C0 33 D2 48 8B CB E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 85 DB 0F 84 ? ? ? ? 80 7B ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 78 ? 33 D2 48 8B CB E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 45 33 C0 48 8D 4C 24 ? 48 8B D0 E8 ? ? ? ? F2 0F 10 38 8B 58 ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 09 48 85 C9 0F 84 ? ? ? ? 48 8B 49 ? 48 85 C9 0F 84 ? ? ? ? 33 D2 E8 ? ? ? ? 48 85 C0 74 ? 45 33 C0 0F 29 74 24 ? 48 8B D0 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 0F 10 30 F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 4C 8B 0D ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? 66 0F 7F 74 24 ? 48 8B CF F2 0F 11 7C 24 ? 89 5C 24 ? E8 ? ? ? ? 0F 28 74 24 ? 0F 28 7C 24 ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24"),
			GamemodeHat, StealHat);
		DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B FA 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 0F 29 7C 24 ? 48 85 FF 74 ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 74 ? 45 33 C9 4C 8B C7 33 D2 48 8B CB E8 ? ? ? ? 45 33 C9 4C 8B C6 B2"),
			GamemodeTag, TagPlayer);*/
		
		auto cLobbyManager = GameAPI::FindMethod("AddPlayerToLobby", 1)->m_pClass;
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cLobbyManager, "StartLobby")),
			LobbyManager, StartLobby);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cLobbyManager, "BanPlayer")),
			LobbyManager, BanPlayer);

		/*DO_HOOK(MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 80 3D ? ? ? ? ? 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05"),
			GameManager, GetPlayersAlive);*/
		
		auto cClientSend = GameAPI::FindMethod("SendSpectating", 1)->m_pClass;
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "PlayerPosition")),
			ClientSend, PlayerPosition);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "PlayerRotation")),
			ClientSend, PlayerRotation);
		DO_HOOK(reinterpret_cast<PVOID>(IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "UseItem")),
			ClientSend, UseItem);

		Unity::il2cppClass* cItemGun = GameAPI::FindMethod("GetHit", 1)->m_pClass;
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cItemGun, "TryUse"),
			ItemGun, TryUse);
		
		Unity::il2cppClass* cItemMelee = NULL;
		for (size_t i = 0; i < GameAPI::cachedMethods.size(); i++)
			if (!strcmp("TryUse", GameAPI::cachedMethods[i]->m_pName)) {
				auto fields = std::vector<Unity::il2cppFieldInfo*>();
				IL2CPP::Class::FetchFields(GameAPI::cachedMethods[i]->m_pClass, &fields);

				for (size_t x = 0; x < fields.size(); x++)
					if (!strcmp("hitFx", fields[x]->m_pName))
						cItemMelee = fields[x]->m_pParentClass;
			}
		DO_HOOK(IL2CPP::Class::Utils::GetMethodPointer(cItemMelee, "TryUse"),
			ItemMelee, TryUse);
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	return true;
}

INL bool Hook::Shutdown()
{
	return MH_Uninitialize();
}