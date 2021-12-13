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
		MEM::PatternScan("GameAssembly.dll", "40 53 48 83 EC ? 80 3D ? ? ? ? ? 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 80 7B ? ? 0F 84 ? ? ? ? 0F 29 74 24 ? 0F 29 7C 24 ? 8B 13 45 33 C0 8B 4B ? E8 ? ? ? ? 33 C9 0F 28 F0 E8 ? ? ? ? 84 C0 74 ? 80 7B ? ? 74 ? 48 8B 0D ? ? ? ? F3 0F 10 7B ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74"));

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
		MEM::FromRelative(reinterpret_cast<PVOID*>(reinterpret_cast<uintptr_t>(IL2CPP::Class::Utils::GetMethodPointer("PlayerInput", "Update")) + 0x21)));
	return *PersistentPlayerData_TypeInfo;
}

PlayerInventory_c* GameAPI::GetInventory()
{
	static auto PlayerInventory_TypeInfo = reinterpret_cast<PlayerInventory_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 80 ? ? ? ? 48 8B 0D ? ? ? ? 8B 50 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D0 48 8B 89 ? ? ? ? 48 89 01 E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B C8 48 8B D8 E8 ? ? ? ? 48 8D 4F ? 48 8B D3 48 89 19 48 8B 5C 24 ? 48 83 C4 ? 5F E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 8B FA", -4));
	return *PlayerInventory_TypeInfo;
}

ItemManager_c* GameAPI::GetItemMgr()
{
	static auto ItemManager_TypeInfo = reinterpret_cast<ItemManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "F2 0F 11 44 24 ? 48 8B 88 ? ? ? ? 48 8B 41 08 48 85 C0 0F 84 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 58 18 F6 81 ? ? ? ? ? 74 0E 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B CB E8 ? ? ? ? 48 8B D8", -4));
	return *ItemManager_TypeInfo;
}

PlayerInput_c* GameAPI::GetPlayerInput()
{
	static auto PlayerManager_TypeInfo = reinterpret_cast<PlayerInput_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "80 3D ? ? ? ? ? 75 1A 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 05 ? ? ? ? C6 05 ? ? ? ? ? F6 80 ? ? ? ? ? 74 18 83 B8 ? ? ? ? ? 75 0F 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B D3 ", -4));
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
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 08 48 85 C9 0F 84 ? ? ? ? 33 D2 E8 ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 85 DB 74 ? 45 33 C0 B2 ? 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 91 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 1A 48 8D 54 24 ? 89 44 24 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 45 33 C0 48 8B D0 E8 ? ? ? ? 48 85 DB 74 ? 48 8B 15 ? ? ? ? 45 33 C9 4C 8B C0 48 8B CB E8 ? ? ? ? 48 83 C4 ? 5B C3 E8 ? ? ? ? CC CC CC CC CC CC 40 53", -4));
	return *PromptManager_TypeInfo;
}

Alerts_c* GameAPI::GetAlertManager()
{
	static auto AlertManager_TypeInfo = reinterpret_cast<Alerts_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 88 ? ? ? ? 48 8B 09 48 85 C9 74 13 48 8B 15 ? ? ? ? 45 33 C0 48 83 C4 28 E9 ? ? ? ? E8 ? ? ? ? CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 60 80 3D ? ? ? ? ?", -4));
	return *AlertManager_TypeInfo;
}

Chatbox_c* GameAPI::GetChatboxManager()
{
	static auto ChatboxManager_TypeInfo = reinterpret_cast<Chatbox_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B D7 48 8B 88 ? ? ? ? 48 89 39 E8 ? ? ? ? 80 3D ? ? ? ? ? 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 80 BF ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 4C 89 64 24 ?", -4));
	return *ChatboxManager_TypeInfo;
}

QuestManager_c* GameAPI::GetQuestManager()
{
	static auto QuestManager_TypeInfo = reinterpret_cast<QuestManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 19 48 8B 88 ? ? ? ? 48 8B 09 48 85 C9 74 ? 4C 8B 05 ? ? ? ? 8B 57 ? E8 ? ? ? ? 48 85 C0 74 ? 33 D2 48 8B C8 E8 ? ? ? ? 4C 8B 05 ? ? ? ? 45 33 C9 48 8B 0D ? ? ? ? 48 8B D0 E8 ? ? ? ? 48 85 DB 74 ? 45 33 C0 48 8B D0 48 8B CB E8 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC 40 53", -4));
	return *QuestManager_TypeInfo;
}

SaveManager_c* GameAPI::GetSaveManager()
{
	static auto SaveManager_TypeInfo = reinterpret_cast<SaveManager_c**>(
		MEM::FromRelative(reinterpret_cast<PVOID*>(reinterpret_cast<uintptr_t>(IL2CPP::Class::Utils::GetMethodPointer("SaveManager", "Awake")) + 0x35)));
	return *SaveManager_TypeInfo;
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

void GameAPI::CompleteDaily() {
	auto instance = GameAPI::GetSaveManager()->static_fields->Instance;
	instance->fields.state->fields.questProgress = 1;
}

void GameAPI::Initialize()
{
	cachedMethods.clear();

	auto classList = std::vector<Unity::il2cppClass*>();
	IL2CPP::Class::FetchClasses(&classList, "Assembly-CSharp", nullptr);

	
	for (size_t i = 0; i < classList.size(); i++) {
		auto methodList = std::vector<Unity::il2cppMethodInfo*>();
		IL2CPP::Class::FetchMethods(classList[i], &methodList);
		
		for (size_t x = 0; x < methodList.size(); x++)
			if (methodList[x]->m_pName[0] > 64 && methodList[x]->m_pName[0] < 123)
				cachedMethods.push_back(methodList[x]);
	}
}

Unity::il2cppMethodInfo* GameAPI::FindMethod(const char* methodName, int args) {
	for (size_t i = 0; i < cachedMethods.size(); i++)
		if (!strcmp(methodName, cachedMethods[i]->m_pName) && (args == -1 || cachedMethods[i]->m_uArgsCount == args))
			return cachedMethods[i];
		return nullptr;
}

void GameAPI::Prompt(const char* header, const char* content) {
	static auto fnNewPrompt = reinterpret_cast<void(__thiscall*)(Prompt_o*, Unity::System_String*, Unity::System_String*, const MethodInfo*)>(
		FindMethod("NewPrompt", 2)->m_pMethodPointer);

	auto sHeader = IL2CPP::String::New(header);
	auto sContent = IL2CPP::String::New(content);
	
	fnNewPrompt(GameAPI::GetPromptManager()->static_fields->Instance, sHeader, sContent, nullptr);
}

void GameAPI::Alert(const char* content)
{
	static auto fnNewAlert = reinterpret_cast<void(__thiscall*)(Alerts_o*, Unity::System_String*, const MethodInfo*)>(
		FindMethod("NewAlert", 1)->m_pMethodPointer);

	Unity::System_String* contentStr = IL2CPP::String::New(content);

	fnNewAlert(GameAPI::GetAlertManager()->static_fields->Instance, contentStr, nullptr);
}

void GameAPI::ChatMessage(const char* message, const char* username, bool useFiltering)
{
	static auto fnAppendMessage = reinterpret_cast<void(__thiscall*)(Chatbox_o*, long fromUser, Unity::System_String*, Unity::System_String*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "40 53 55 56 57 41 54 48 83 EC 40 80 3D ? ? ? ? ?"));
	
	static auto colorSyntax1 = reinterpret_cast<Unity::System_String**>(
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? C6 05 ? ? ? ? ? 45 33 E4 44 38 25 ? ? ? ? 44 89 A4 24", -4));
	static auto charGreaterThan = reinterpret_cast<Unity::System_String**>(
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? C6 05 ? ? ? ? ? 45 33 E4 44 38 25 ? ? ? ? 44 89 A4 24", -16));
	static auto colorSyntax2 = reinterpret_cast<Unity::System_String**>(
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? C6 05 ? ? ? ? ? 45 33 E4 44 38 25 ? ? ? ? 44 89 A4 24", -40));
	static auto charColon = reinterpret_cast<Unity::System_String**>(
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? C6 05 ? ? ? ? ? 45 33 E4 44 38 25 ? ? ? ? 44 89 A4 24", -52));
	static auto charHashtag = reinterpret_cast<Unity::System_String**>(
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? C6 05 ? ? ? ? ? 45 33 E4 44 38 25 ? ? ? ? 44 89 A4 24", -64));

	auto chatboxInstance = GameAPI::GetChatboxManager()->static_fields->Instance;

	if (!chatboxInstance)
		return;

	if (!useFiltering) {
		Unity::System_String* oColorSyntax1 = *colorSyntax1;
		Unity::System_String* oCharGreaterThan = *charGreaterThan;
		Unity::System_String* oColorSyntax2 = *colorSyntax2;
		Unity::System_String* oCharColon = *charColon;
		Unity::System_String* oCharHashtag = *charHashtag;

		static auto placeholderStr = IL2CPP::String::New("`");

		DWORD oldProtect = 0;

		VirtualProtect(*colorSyntax1, sizeof(Unity::System_String*), PAGE_EXECUTE_READWRITE, &oldProtect);
		VirtualProtect(*charGreaterThan, sizeof(Unity::System_String*), PAGE_EXECUTE_READWRITE, nullptr);
		VirtualProtect(*colorSyntax2, sizeof(Unity::System_String*), PAGE_EXECUTE_READWRITE, nullptr);
		VirtualProtect(*charColon, sizeof(Unity::System_String*), PAGE_EXECUTE_READWRITE, nullptr);
		VirtualProtect(*charHashtag, sizeof(Unity::System_String*), PAGE_EXECUTE_READWRITE, nullptr);

		*colorSyntax1 = placeholderStr;
		*charGreaterThan = placeholderStr;
		*colorSyntax2 = placeholderStr;
		*charColon = placeholderStr;
		*charHashtag = placeholderStr;

		fnAppendMessage(chatboxInstance, 1, IL2CPP::String::New(message), IL2CPP::String::New(username), nullptr);

		*colorSyntax1 = oColorSyntax1;
		*charGreaterThan = oCharGreaterThan;
		*colorSyntax2 = oColorSyntax2;
		*charColon = oCharColon;
		*charHashtag = oCharHashtag;

		VirtualProtect(*charGreaterThan, sizeof(Unity::System_String*), oldProtect, nullptr);
		VirtualProtect(*colorSyntax2, sizeof(Unity::System_String*), oldProtect, nullptr);
		VirtualProtect(*charColon, sizeof(Unity::System_String*), oldProtect, nullptr);
		VirtualProtect(*charHashtag, sizeof(Unity::System_String*), oldProtect, nullptr);
		VirtualProtect(*colorSyntax1, sizeof(Unity::System_String*), oldProtect, nullptr);
	} else
		fnAppendMessage(chatboxInstance, 1, IL2CPP::String::New(message), IL2CPP::String::New(username), nullptr);
}

bool GameAPI::Raycast(UnityEngine_Vector3_o origin, UnityEngine_Vector3_o dir, UnityEngine_RaycastHit_o* hitInfo, float maxDistance, int layerMask)
{
	return false;
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

UnityEngine_Vector3_o GameAPI::GetRight(UnityEngine_Transform_o* pThis)
{
	static auto fnGetForward = reinterpret_cast<UnityEngine_Vector3_o * (__thiscall*)(UnityEngine_Vector3_o*, UnityEngine_Transform_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 33 C0 0F 57 C0 48 89 01 48 8B FA 89 41 ? 48 8B D9 48 8B 05 ? ? ? ? 0F 11 44 24 ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8D 54 24 ? 48 8B CF FF D0 33 D2 48 8D 4C 24 ? E8 ? ? ? ? 45 33 C9 4C 8D 44 24 ? 48 8D 54 24 ? 48 8D 4C 24 ? F2 0F 10 00 8B 40 ? F2 0F 11 44 24 ? 0F 10 44 24 ? 89 44 24 ? 66 0F 7F 44 24 ? E8 ? ? ? ? F2 0F 10 00 8B 40 ? F2 0F 11 03 89 43 ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 0F 57 C0 48 8B FA 48 8B D9 0F 11 01 48 85 C0"));
	UnityEngine_Vector3_o out = {};
	fnGetForward(&out, pThis, nullptr);
	return out;
}

float GameAPI::DeltaTime()
{
	static auto fnGetDeltaTime = reinterpret_cast<float(__thiscall*)(const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 48 83 EC"));
	return fnGetDeltaTime(nullptr);
}

void GameAPI::Teleport(UnityEngine_Vector3_o pos)
{
	static auto fnSetPosition = reinterpret_cast<void(__thiscall*)(UnityEngine_Rigidbody_o*, UnityEngine_Vector3_o, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF FF D0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF FF D0 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 74 24"));

	auto rb = GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerMovement->fields.rb;

	fnSetPosition(rb, pos, nullptr);
}
