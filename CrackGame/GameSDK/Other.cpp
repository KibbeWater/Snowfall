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
	static auto GameManager_TypeInfo = reinterpret_cast<GameManager_c*>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 91 ? ? ? ? 48 8B 0A 48 85 C9 74 2C F2 0F 10 00 4C 8D 44 24 ? 8B 40 08 45 33 C9 48 8B D7 F2 0F 11 44 24 ? 89 44 24 28", -4));
	return GameManager_TypeInfo;
}

SteamManager_c* GameAPI::GetSteammanager()
{
	static auto SteamManager_TypeInfo = reinterpret_cast<SteamManager_c*>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 89 ? ? ? ? 48 89 19 48 8B D3 E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 89 53 18 48 8D 4B 18 E8 ? ? ? ? 90 33 C9", -4));
	return SteamManager_TypeInfo;
}

PersistentPlayerData_c* GameAPI::GetPersistentData()
{
	static auto PersistentPlayerData_TypeInfo = reinterpret_cast<PersistentPlayerData_c*>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B D3 48 8B 88 ? ? ? ? 48 83 C1 08 48 89 19 E8 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 F6 81 ? ? ? ? ? 74 0E 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 D2", -4));
	return PersistentPlayerData_TypeInfo;
}

void GameAPI::RespawnPlayer(UnityEngine_Vector3_o pos)
{
	static auto fnRespawnPlayer = reinterpret_cast<void(__thiscall*)(GameManager_o*, long, UnityEngine_Vector3_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 80 3D ? ? ? ? ? 49 8B F0 48 8B FA 48 8B D9 75 43"));
	
	if (!G::pGameManager || !G::pPlayerManager)
		return;

	return fnRespawnPlayer(GameAPI::GetGamemanager()->static_fields->Instance, GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.Value, pos, nullptr);
}

void GameAPI::TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged)
{
	static auto fnSendTagPlayer = reinterpret_cast<void(__thiscall*)(GameModeBombTag_o*, long, long, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B DA 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 45 33 C0 48 8B D6 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 8B 0D ? ? ? ? 8B F8 48 8B 91 ? ? ? ? 48 8B 0A 48 85 C9 74 ? 33 D2 E8 ? ? ? ? 45 33 C9 44 8B C0 8B D7 48 8B CE E8 ? ? ? ? 48 85 DB 74 ? 45 33 C0 8B D7 48 8B CB E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B DA"));
	
	return fnSendTagPlayer(pThis, tagger, tagged, nullptr);
}

void GameAPI::DamagePlayer(long hurtPlayerId, int damage, int itemID, int objectID)
{
	static auto fnDamagePlayer = reinterpret_cast<void(__thiscall*)(long, int, UnityEngine_Vector3_o, int, int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 45 8B E1 "));

	UnityEngine_Vector3_o emptyDir = {};

	return fnDamagePlayer(hurtPlayerId, damage, emptyDir, itemID, objectID, nullptr);
}
