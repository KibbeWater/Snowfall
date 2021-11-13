#include "pch.h"

bool Obfuscation::DecryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o pThis)
{
	static auto fnDecryptBool = reinterpret_cast<int(__thiscall*)(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "33 D2 E9 ? ? ? ? CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 20 80 79 08 00"));

	return fnDecryptBool(pThis, nullptr);
}

int Obfuscation::DecryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o pThis)
{
	static auto fnDecryptInt = reinterpret_cast<int(__thiscall*)(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "33 D2 E9 ? ? ? ? CC CC CC CC CC CC CC CC CC 40 53 48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 33 D2 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B D0 48 8B CB E8 ? ? ? ? CC CC 48 89 5C 24 ? 57 48 83 EC 20 80 79 08 00"));

	return fnDecryptInt(pThis, nullptr);
}

float Obfuscation::DecryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* pThis)
{
	static auto fnDecryptFloat = reinterpret_cast<float(__thiscall*)(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 83 EC ? 33 D2 E8 ? ? ? ? 48 83 C4 ? C3 40 53 48 83 EC ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 33 D2 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B D0 48 8B CB E8 ? ? ? ? CC CC 48 83 EC ? 33 D2 E8 ? ? ? ? 33 D2 F3 0F 11 44 24"));

	return fnDecryptFloat(pThis, nullptr);
}

void Obfuscation::EncryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o* obscuredBool, bool value)
{
	obscuredBool->fields.hiddenValue = obscuredBool->fields.currentCryptoKey ^ (32 * value + 181);
}

void Obfuscation::EncryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o* obscuredInt, int value)
{
	obscuredInt->fields.hiddenValue = value ^ obscuredInt->fields.currentCryptoKey;
}

void Obfuscation::EncryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* obscuredInt, float value)
{
	static auto fnXorFloatToInt = reinterpret_cast<int(__thiscall*)(float, int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 83 EC 28 F3 0F 11 44 24 ?"));

	obscuredInt->fields.hiddenValue = fnXorFloatToInt(value, obscuredInt->fields.currentCryptoKey, nullptr);
}

GameManager_c* GameAPI::GetGamemanager()
{
	static auto GameManager_TypeInfo = reinterpret_cast<GameManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 91 ? ? ? ? 48 8B 0A 48 85 C9 74 2C F2 0F 10 00 4C 8D 44 24 ? 8B 40 08 45 33 C9 48 8B D7 F2 0F 11 44 24 ? 89 44 24 28", -4));
	return *GameManager_TypeInfo;
}

SteamManager_c* GameAPI::GetSteammanager()
{
	static auto SteamManager_TypeInfo = reinterpret_cast<SteamManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 89 ? ? ? ? 48 89 19 48 8B D3 E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 89 53 18 48 8D 4B 18 E8 ? ? ? ? 90 33 C9", -4));
	return *SteamManager_TypeInfo;
}

PersistentPlayerData_c* GameAPI::GetPersistentData()
{
	static auto PersistentPlayerData_TypeInfo = reinterpret_cast<PersistentPlayerData_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B D3 48 8B 88 ? ? ? ? 48 83 C1 08 48 89 19 E8 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 F6 81 ? ? ? ? ? 74 0E 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 D2", -4));
	return *PersistentPlayerData_TypeInfo;
}

PlayerInventory_c* GameAPI::GetInventory()
{
	static auto PlayerInventory_TypeInfo = reinterpret_cast<PlayerInventory_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B D0 48 8B 89 ? ? ? ? 48 89 01 E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 4F 18 48 8B D3", -4));
	return *PlayerInventory_TypeInfo;
}

ItemManager_c* GameAPI::GetItemMgr()
{
	static auto ItemManager_TypeInfo = reinterpret_cast<ItemManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B D3 48 8B 88 ? ? ? ? 48 83 C1 08 48 89 19 E8 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 F6 81 ? ? ? ? ? 74 0E 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 80 3D ? ", -4));
	return *ItemManager_TypeInfo;
}

PlayerInput_c* GameAPI::GetPlayerInput()
{
	static auto PlayerManager_TypeInfo = reinterpret_cast<PlayerInput_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 88 ? ? ? ? 48 8B D7 48 83 C1 08 48 89 5C 24 ? 48 89 39 E8 ? ? ? ? 48 8B 15 ? ? ? ?", -4));
	return *PlayerManager_TypeInfo;
}

LobbyManager_c* GameAPI::GetLobbyManager()
{
	static auto LobbyManager_TypeInfo = reinterpret_cast<LobbyManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 88 ? ? ? ? 48 8B D7 48 83 C1 10", -4));
	return *LobbyManager_TypeInfo;
}

Prompt_c* GameAPI::GetPromptManager()
{
	static auto PromptManager_TypeInfo = reinterpret_cast<Prompt_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B D7 48 8B 88 ? ? ? ? 48 89 39 E8 ? ? ? ? 33 D2 48 8B CF E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 ", -4));
	return *PromptManager_TypeInfo;
}

void GameAPI::SetLockState(ELockState lockState)
{
	static auto fnSetLockState = reinterpret_cast<void(__thiscall*)(int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 48 8B 05 ? ? ? ? 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 8B CB 48 83 C4 ? 5B 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 0F B6 D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 0F B6 CB 48 83 C4 ? 5B 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 80 3D"));
	return fnSetLockState((int)lockState, nullptr);
}

ELockState GameAPI::GetLockState()
{
	static auto fnGetLockState = reinterpret_cast<int(__thiscall*)(const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 8B CB 48 83 C4 ? 5B 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 0F B6 D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 0F B6 CB 48 83 C4 ? 5B 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 80 3D"));
	return (ELockState)fnGetLockState(nullptr);
}

void GameAPI::RespawnPlayer(UnityEngine_Vector3_o pos)
{
	static auto fnRespawnPlayer = reinterpret_cast<void(__thiscall*)(GameManager_o*, long, UnityEngine_Vector3_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 80 3D ? ? ? ? ? 49 8B F0 48 8B FA 48 8B D9 75 43"));

	return fnRespawnPlayer(GameAPI::GetGamemanager()->static_fields->Instance, GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.m_SteamID, pos, nullptr);
}

void GameAPI::TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged)
{
	static auto fnTagPlayer = reinterpret_cast<void(__thiscall*)(GameModeBombTag_o*, long, long, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B DA 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 45 33 C0 48 8B D6 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 8B 0D ? ? ? ? 8B F8 48 8B 91 ? ? ? ? 48 8B 0A 48 85 C9 74 ? 33 D2 E8 ? ? ? ? 45 33 C9 44 8B C0 8B D7 48 8B CE E8 ? ? ? ? 48 85 DB 74 ? 45 33 C0 8B D7 48 8B CB E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B DA"));
	
	return fnTagPlayer(pThis, tagger, tagged, nullptr);
}

void GameAPI::DamagePlayer(long hurtPlayerId, int damage, int itemID, int objectID, UnityEngine_Vector3_o dmgDir)
{
	static auto fnDamagePlayer = reinterpret_cast<void(__thiscall*)(long, int, UnityEngine_Vector3_o, int, int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 45 8B E1 "));

	return fnDamagePlayer(hurtPlayerId, damage, dmgDir, itemID, objectID, nullptr);
}

ItemData_o* GameAPI::GetItemByID(int ID)
{
	static auto fnGetItemByID = reinterpret_cast<ItemData_o*(__thiscall*)(int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 80 3D ? ? ? ? ? 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05"));

	return fnGetItemByID(ID, nullptr);
}

void GameAPI::ForceGiveItem(ItemData_o* item) noexcept
{
	static auto fnForceGiveItem = reinterpret_cast<void(__thiscall*)(PlayerInventory_o*, ItemData_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B DA 48 8B F9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 89 74 24 ? 4C 89 74 24 ? 48 85 DB 0F 84 ? ? ? ? 48 8B 05 ? ? ? ? 8B 73 ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 45 33 C0 8B CE 48 8B 10 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 63 F0 48 8B 91 ? ? ? ? 4C 8B 32 4D 85 F6 0F 84 ? ? ? ? 49 8B 16 48 8B CB 48 8B 52 ? E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 48 8B C6 41 3B 76 ? 0F 83 ? ? ? ? 48 83 C0 ? 48 89 6C 24 ? 49 8D 0C C6 48 8B D3 48 89 19 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 6F ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 45 33 C0 33 D2 48 8B CD E8 ? ? ? ? 84 C0 74 ? 89 77 ? 8B D6 EB ? 8B 57 ? 3B F2 75 ? 45 33 C0 48 8B CF E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 29 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 33 D2 48 8B CD E8 ? ? ? ? 48 8B 6C 24 ? 84 C0 74 ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 09 48 85 C9 74 ? 45 33 C9 44 8B C6 48 8B D3 E8 ? ? ? ? 33 D2 48 8B CF 4C 8B 74 24 ? 48 8B 74 24 ? 48 8B 5C 24 ? 48 83 C4 ? 5F E9 ? ? ? ? E8 ? ? ? ? CC E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? CC E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9"));

	return fnForceGiveItem(GameAPI::GetInventory()->static_fields->Instance, item, nullptr);
}

void GameAPI::BanPlayer(long ID)
{
	static auto oBanPlayer = static_cast<decltype(&Hook::LobbyManager::hkBanPlayer)>(Hook::LobbyManager::pBanPlayer);

	oBanPlayer(GameAPI::GetLobbyManager()->static_fields->Instance, ID, nullptr);
}

bool GameAPI::Raycast(UnityEngine_Vector3_o origin, UnityEngine_Vector3_o dir, UnityEngine_RaycastHit_o* hitInfo, float maxDistance, int layerMask)
{
	static auto fnRaycast = reinterpret_cast<bool(__thiscall*)(UnityEngine_Ray_o*, UnityEngine_RaycastHit_o*, float, int32_t, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 8B C4 48 89 58 ? 55 56 57 41 56"));

	UnityEngine_Ray_o ray = {};
	ray.fields.m_Origin = origin;
	ray.fields.m_Direction = dir;

	return fnRaycast(&ray, hitInfo, maxDistance, layerMask, nullptr);
}

UnityEngine_Vector3_o GameAPI::GetPosition(UnityEngine_Transform_o* pThis)
{
	static auto fnGetPosition = reinterpret_cast<UnityEngine_Vector3_o(__thiscall*)(UnityEngine_Transform_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 33 C0 48 8B FA 48 89 01 48 8B D9 89 41 ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF FF D0 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 33 C0"));
	return fnGetPosition(pThis, nullptr);
}

UnityEngine_Vector3_o GameAPI::GetForward(UnityEngine_Transform_o* pThis)
{
	static auto fnGetForward = reinterpret_cast<UnityEngine_Vector3_o*(__thiscall*)(UnityEngine_Vector3_o*, UnityEngine_Transform_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 33 C0 0F 57 C0 48 89 01 48 8B FA 89 41 ? 48 8B D9 48 8B 05 ? ? ? ? 0F 11 44 24 ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8D 54 24 ? 48 8B CF FF D0 33 D2 48 8D 4C 24 ? E8 ? ? ? ? 45 33 C9 4C 8D 44 24 ? 48 8D 54 24 ? 48 8D 4C 24 ? F2 0F 10 00 8B 40 ? F2 0F 11 44 24 ? 0F 10 44 24 ? 89 44 24 ? 66 0F 7F 44 24 ? E8 ? ? ? ? F2 0F 10 00 8B 40 ? F2 0F 11 03 89 43 ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 33 C0"));
	UnityEngine_Vector3_o out = {};
	fnGetForward(&out, pThis, nullptr);
	return out;
}

void GameAPI::Teleport(UnityEngine_Vector3_o pos)
{
	static auto fnSetPosition = reinterpret_cast<void(__thiscall*)(UnityEngine_Rigidbody_o*, UnityEngine_Vector3_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF FF D0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF FF D0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 0F B6 DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 0F B6 D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57"));

	auto rb = GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerMovement->fields.rb;

	fnSetPosition(rb, pos, nullptr);
}
