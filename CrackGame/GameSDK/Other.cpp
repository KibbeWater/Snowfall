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
		MEM::PatternScan("GameAssembly.dll", "33 D2 E9 ? ? ? ? CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 20 80 79 0C 00 48 8B FA 48 8B D9 75 28"));

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

	return fnRespawnPlayer(GameAPI::GetGamemanager()->static_fields->Instance, GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.Value, pos, nullptr);
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

void GameAPI::ForceGiveItem(ItemData_o* item)
{
	static auto fnForceGiveItem = reinterpret_cast<void(__thiscall*)(PlayerInventory_o*, ItemData_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC 20 80 3D ? ? ? ? ? 48 8B DA 48 8B F9 75 2B 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 89 74 24 ? 4C 89 74 24 ?"));

	return fnForceGiveItem(GameAPI::GetInventory()->static_fields->Instance, item, nullptr);
}

void GameAPI::SendPacket(Packet_o* packet)
{
	static auto fnSendPacket = reinterpret_cast<void(__thiscall*)(Packet_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 8B 78 ? 48 85 DB 0F 84 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 8D 14 38 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 89 51 ? 33 D2 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? FF 01 48 8B CB E8 ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 4C 8B 10 4D 85 D2 74 ? 48 8B 05 ? ? ? ? 41 B9 ? ? ? ? 48 8B D3 48 C7 44 24 ? ? ? ? ? 48 8B 88 ? ? ? ? 44 8B 41 ? 49 8B 4A ? E8 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B F2 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 8B 78 ? 48 85 DB 74 ? 33 D2 48 8B CB E8 ? ? ? ? 8D 14 38 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 89 51 ? 33 D2 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? FF 01 48 8B CB E8 ? ? ? ? 48 8B 05 ? ? ? ? 41 B9 ? ? ? ? 48 8B D3 48 C7 44 24 ? ? ? ? ? 48 8B 88 ? ? ? ? 44 8B 41 ? 48 8B CE E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9"));

	return fnSendPacket(packet, nullptr);
}
