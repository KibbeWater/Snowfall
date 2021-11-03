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

CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o Obfuscation::EncryptBool(bool value, short key)
{
	static auto fnEncrypt = reinterpret_cast<int(__thiscall*)(bool, short, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "66 90 0F B6 C1 C1 E0 05"));
	static auto fnFromEncrypted = reinterpret_cast<CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o(__thiscall*)(int, short, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 33 D2 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B D0 48 8B CB E8 ? ? ? ? CC CC 40 53 48 83 EC 20 33 C0 48 8B D9 48 89 01 89 41 08"));

	int encryptedVal = fnEncrypt(value, key, nullptr);
	return fnFromEncrypted(encryptedVal, key, nullptr);
}

CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o Obfuscation::EncryptInt(int value)
{
	static auto fnEncrypt = reinterpret_cast<int(__thiscall*)(int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 33 D2 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B D0 48 8B CB E8 ? ? ? ? CC CC 48 83 EC 48 44 8B 01"));
	static auto fnFromEncrypted = reinterpret_cast<CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o(__thiscall*)(int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 33 D2 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B D0 48 8B CB E8 ? ? ? ? CC CC 40 53 48 83 EC 20 0F 57 C0 33 C0 0F 11 01 89 41 10"));

	int encryptedVal = fnEncrypt(value, nullptr);
	return fnFromEncrypted(encryptedVal, nullptr);
}

int Obfuscation::EncryptFloat(float value, int key)
{
	static auto fnEncrypt = reinterpret_cast<int(__thiscall*)(float, int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "45 33 C0 E9 ? ? ? ? CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 40 80 3D ? ? ? ? ? 48 8B DA 48 8B F9 75 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 85 DB"));
	static auto fnFromEncrypted = reinterpret_cast<CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o(__thiscall*)(int, int, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC 20 80 79 0C 00 48 8B FA 48 8B D9 75 28"));

	int encryptedVal = fnEncrypt(value, key, nullptr);
	//auto encrypted = fnFromEncrypted(encryptedVal, key, nullptr);
	return encryptedVal;
}

void GameAPI::RespawnPlayer(UnityEngine_Vector3_o pos)
{
	static auto fnRespawnPlayer = reinterpret_cast<void(__thiscall*)(GameManager_o*, long, UnityEngine_Vector3_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 80 3D ? ? ? ? ? 49 8B F0 48 8B FA 48 8B D9 75 43"));
	
	if (!G::pGameManager || !G::pPlayerManager)
		return;

	return fnRespawnPlayer(G::pGameManager, (long)G::pPlayerManager->fields.steamProfile.fields.Id.fields.Value, pos, nullptr);
}

void GameAPI::TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged)
{
	static auto fnSendTagPlayer = reinterpret_cast<void(__thiscall*)(GameModeBombTag_o*, long, long, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B DA 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 45 33 C0 48 8B D6 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 8B 0D ? ? ? ? 8B F8 48 8B 91 ? ? ? ? 48 8B 0A 48 85 C9 74 ? 33 D2 E8 ? ? ? ? 45 33 C9 44 8B C0 8B D7 48 8B CE E8 ? ? ? ? 48 85 DB 74 ? 45 33 C0 8B D7 48 8B CB E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F0 48 8B DA"));
	
	return fnSendTagPlayer(pThis, tagger, tagged, nullptr);
}
