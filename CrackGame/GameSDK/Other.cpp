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

long Packet::ReadLong(Packet_o* packet) {
	return *reinterpret_cast<long*>(&packet->fields.readableBuffer->m_Items + packet->fields.readPos);
}

void Packet::ResetPacket(Packet_o* packet) {
	packet->fields.readPos = 0;
}

GameManager_c* GameAPI::GetGamemanager()
{
	static auto SpawnSpectator = GameAPI::FindMethod("SpawnSpectator", 1);
	return reinterpret_cast<GameManager_c*>(SpawnSpectator->m_pClass);
}

PlayerServerCommunication_c* GameAPI::GetServerCommunicator() {
	static auto PlayerServerCommunication = FindClassByField("idToDistance", "ForceMovementUpdate");
	return reinterpret_cast<PlayerServerCommunication_c*>(PlayerServerCommunication);
}

SteamManager_c* GameAPI::GetSteammanager() {
	static auto SteamManager_TypeInfo = reinterpret_cast<SteamManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "48 8B 89 ? ? ? ? 48 89 19 48 8B D3 E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 89 53 18 48 8D 4B 18 E8 ? ? ? ? 90 33 C9", -4));
	return *SteamManager_TypeInfo;
}

PersistentPlayerData_c* GameAPI::GetPersistentData() {
	static auto PersistentPlayerData = FindClassByField("hnsFrozen", "Awake");
	return reinterpret_cast<PersistentPlayerData_c*>(PersistentPlayerData);
}

PlayerInventory_c* GameAPI::GetInventory() {
	static auto LockInventory = GameAPI::FindMethod("LockInventory", 1);
	return reinterpret_cast<PlayerInventory_c*>(LockInventory->m_pClass);
}

ItemManager_c* GameAPI::GetItemMgr()
{
	static auto ItemManager_TypeInfo = reinterpret_cast<ItemManager_c**>(
		MEM::PatternScanRel("GameAssembly.dll", "F2 0F 11 44 24 ? 48 8B 88 ? ? ? ? 48 8B 41 08 48 85 C0 0F 84 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 58 18 F6 81 ? ? ? ? ? 74 0E 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B CB E8 ? ? ? ? 48 8B D8", -4));
	return *ItemManager_TypeInfo;
}

PlayerInput_c* GameAPI::GetPlayerInput()
{
	auto StopInput = GameAPI::FindMethod("StopInput", 0);
	auto PlayerInput = reinterpret_cast<PlayerInput_c*>(StopInput->m_pClass);

	return PlayerInput;
}

LobbyManager_c* GameAPI::GetLobbyManager()
{
	auto LobbyLoop = GameAPI::FindMethod("LobbyLoop", 0);
	auto LobbyManager = reinterpret_cast<LobbyManager_c*>(LobbyLoop->m_pClass);

	return LobbyManager;
}

GameLoop_c* GameAPI::GetGameLoopManager() {
	auto StartGames = GameAPI::FindMethod("StartGames", 0);
	auto GameLoop = reinterpret_cast<GameLoop_c*>(StartGames->m_pClass);

	return GameLoop;
}

Prompt_c* GameAPI::GetPromptManager()
{
	auto NewPrompt = GameAPI::FindMethod("NewPrompt", 2);
	auto Prompt = reinterpret_cast<Prompt_c*>(NewPrompt->m_pClass);

	return Prompt;
}

Alerts_c* GameAPI::GetAlertManager()
{
	auto NewAlert = GameAPI::FindMethod("NewAlert", 1);
	auto Alert = reinterpret_cast<Alerts_c*>(NewAlert->m_pClass);

	return Alert;
}

Chatbox_c* GameAPI::GetChatboxManager() {
	static auto AppendMessage = GameAPI::FindMethod("AppendMessage", 3);
	auto Chatbox = reinterpret_cast<Chatbox_c*>(AppendMessage->m_pClass);

	return Chatbox;
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

void GameAPI::DamagePlayer(unsigned long hurtPlayerId, int damage, UnityEngine_Vector3_o dmgDir, int itemID, int objectID)
{
	static auto fnDamagePlayer = reinterpret_cast<void(__thiscall*)(unsigned long, int, UnityEngine_Vector3_o, int, int, const MethodInfo*)>(GameAPI::FindMethod("DamagePlayer", 5)->m_pMethodPointer);

	return fnDamagePlayer(hurtPlayerId, damage, dmgDir, itemID, objectID, nullptr);
}

void GameAPI::PunchPlayer(unsigned long punchTargetId, UnityEngine_Vector3_o dmgDir) {
	static auto fnPunchPlayer = reinterpret_cast<void(__thiscall*)(unsigned long, UnityEngine_Vector3_o, const MethodInfo*)>(
		IL2CPP::Class::Utils::GetMethodPointer(
			GameAPI::FindMethod("SendSpectating", 1)->m_pClass,
			"PunchPlayer"
		)
	);

	return fnPunchPlayer(punchTargetId, dmgDir, nullptr);
}

ItemData_o* GameAPI::GetItemByID(int ID) {
	static auto fnGetItemById = reinterpret_cast<ItemData_o*(__thiscall*)(int, const MethodInfo*)>(
		GameAPI::FindMethod("GetItemById", 1)->m_pMethodPointer);

	return fnGetItemById(ID, nullptr);
}

void GameAPI::ForceGiveItem(ItemData_o* item) noexcept {
	static auto fnForceGiveItem = reinterpret_cast<void(__thiscall*)(PlayerInventory_o*, ItemData_o*, const MethodInfo*)>(
		IL2CPP::Class::Utils::GetMethodPointer(GameAPI::FindMethod("LockInventory", 1)->m_pClass, "ForceGiveItem"));

	auto inventory = GameAPI::GetInventory();

	return fnForceGiveItem(inventory->static_fields->Instance, item, nullptr);
}

void GameAPI::BanPlayer(long ID) {
	static auto oBanPlayer = static_cast<decltype(&Hook::LobbyManager::hkBanPlayer)>(Hook::LobbyManager::pBanPlayer);

	oBanPlayer(GameAPI::GetLobbyManager()->static_fields->Instance, ID, nullptr);
}

bool GameAPI::TrySnowballReload() {
	std::string m_sObjectSubstring = "SnowballPile";

	Unity::il2cppClass* m_pSystemTypeClass = IL2CPP::Class::Find("UnityEngine.GameObject");
	auto m_pSystemType = IL2CPP::Class::GetSystemType(m_pSystemTypeClass);
	auto m_pObjects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(m_pSystemType);

	auto myPos = new Vector3(reinterpret_cast<Unity::CTransform*>(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerCam)->GetPosition());
	static float maxDist = 12.0;

	for (uintptr_t u = 0U; m_pObjects->m_uMaxLength > u; ++u) {
		Unity::CGameObject* m_pObject = m_pObjects->At(u);
		if (!m_pObject) continue; // Just in-case

		// Obtaining object name and then converting it to std::string
		std::string m_sObjectName = m_pObject->GetName()->ToString();
		if (m_sObjectName.find(m_sObjectSubstring) != std::string::npos) {
			auto pilePos = new Vector3(m_pObject->GetTransform()->GetPosition());
			auto dist = pilePos->distanceTo(*myPos);
			if (dist <= maxDist && M::pSnowballPileInteract != nullptr) {
				static Unity::il2cppClass* m_pSystemTypeClass = reinterpret_cast<Unity::il2cppClass*>(M::pSnowballPileInteract->klass);
				auto m_pSystemType = IL2CPP::Class::GetSystemType(m_pSystemTypeClass);

				auto components = m_pObject->GetComponents(m_pSystemType);
				if (components->m_uMaxLength <= 0) continue;
				auto component = components->At(0);

				SnowballPileInteract_o* pile = reinterpret_cast<SnowballPileInteract_o*>(component);

				static auto fnTryInteract = reinterpret_cast<void(UNITY_CALLING_CONVENTION)(SnowballPileInteract_o*)>(
					IL2CPP::Class::Utils::GetMethodPointer(m_pSystemTypeClass, "TryInteract"));
				
				fnTryInteract(pile);
				return true;
			}
		}
	}
	return false;
}

void GameAPI::BreakAll() {
	static auto cGlassBreak = GameAPI::FindMethod("MakeSolid", 0)->m_pClass;
	auto m_pSystemType = IL2CPP::Class::GetSystemType(cGlassBreak);
	auto m_pComponents = Unity::Object::FindObjectsOfType<Unity::CComponent>(m_pSystemType);

	for (uintptr_t u = 0U; m_pComponents->m_uMaxLength > u; ++u) {
		Unity::CComponent* m_pComponent = m_pComponents->At(u);
		if (!m_pComponent) continue; // Just in-case

		static auto fnTryInteract = reinterpret_cast<void(UNITY_CALLING_CONVENTION)(GlassBreak_o*)>(
			IL2CPP::Class::Utils::GetMethodPointer(cGlassBreak, "TryInteract"));

		fnTryInteract(reinterpret_cast<GlassBreak_o*>(m_pComponent));
	}
}

void GameAPI::TakeAllTiles() {
	static auto cTile = GameAPI::FindMethod("SetTileId", 1)->m_pClass;
	auto m_pSystemType = IL2CPP::Class::GetSystemType(cTile);
	auto m_pComponents = Unity::Object::FindObjectsOfType<Unity::CComponent>(m_pSystemType);

	for (uintptr_t u = 0U; m_pComponents->m_uMaxLength > u; ++u) {
		Unity::CComponent* m_pComponent = m_pComponents->At(u);
		if (!m_pComponent) continue; // Just in-case
		
		auto obj = m_pComponent->GetMemberValue<Unity::CGameObject*>("gameObject");
		G::vPositionOverrideQueue.push_back(new Vector3(obj->GetTransform()->GetPosition()));
		/* Teleport((Vector3(obj->GetTransform()->GetPosition()) - Vector3(0,.5,0)).ToEngine());
		Sleep(100); */
	}
}

void GameAPI::DropItem(int slot) {
	static auto cPlayerInventory = GameAPI::FindMethod("TryDropItem", 1)->m_pClass;
	static auto fnTryDropItem = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(PlayerInventory_o*, int)>(
		IL2CPP::Class::Utils::GetMethodPointer(cPlayerInventory, "TryDropItem"));

	fnTryDropItem(GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerInventory, slot);
}

std::vector<ItemData_o*> GameAPI::GetItems() {
	std::vector<ItemData_o*> items = std::vector<ItemData_o*>();

	auto inv = GetInventory()->static_fields->inventory;
	for (size_t i = 0; i < inv->max_length; i++)
		items.push_back(inv->m_Items[i]);
	return items;
}

ItemData_o* GameAPI::FindItemById(int itemId) {
	auto items = GetItems();
	ItemData_o* selItem = nullptr;
	for (size_t i = 0; i < items.size(); i++)
		if (items.at(i)->fields.itemID == itemId)
			selItem = items.at(i);
	return selItem;
}

void GameAPI::CompleteDaily() {
	auto instance = GameAPI::GetSaveManager()->static_fields->Instance;
	instance->fields.state->fields.questProgress = 1;
}

void GameAPI::CSendPosition(UnityEngine_Vector3_o* vec) {
	static auto PlayerServerCommunication = FindClassByField("idToDistance", "ForceMovementUpdate");

	/* static auto fnForceMovementUpdate = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(const MethodInfo*)>(
			IL2CPP::Class::Utils::GetMethodPointer(PlayerServerCommunication, "ForceMovementUpdate")); */



			/* static auto cClientSend = reinterpret_cast<Unity::CComponent*>(GameAPI::FindMethod("SendSpectating", 1)->m_pClass); */
			/* static auto fnPlayerPosition = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(UnityEngine_Vector3_o*, uint64_t)>(
				IL2CPP::Class::Utils::GetMethodPointer(cClientSend, "PlayerPosition")); */

				/* static auto fnForceMovementUpdate = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(const MethodInfo*)>(
					IL2CPP::Class::Utils::GetMethodPointer(PlayerServerCommunication, "ForceMovementUpdate")); */

					/* static auto cPlayerServerCommunication = reinterpret_cast<Unity::CComponent*>(GameAPI::FindMethod("SendSpectating", 1)->m_pClass); */

	auto pos = (new Vector3(*vec))->ToEngine(); // 40 55 56 41 57 48 83 EC 30 80 3D ? ? ? ? ? 41 8B F0 4C 8B FA 48 8B E9 75 37 48 8D 0D ? ? ? ? E8 ? ? ? ? 

	static auto fnSendPositionToAll = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(PlayerServerCommunication_o*, UnityEngine_Vector3_o*, ERenderDistance)>(
		MEM::PatternScan("GameAssembly.dll", "40 55 56 41 57 48 83 EC 30 80 3D ? ? ? ? ? 41 8B F0 4C 8B FA 48 8B E9 75 37 48 8D 0D ? ? ? ? E8 ? ? ? ?"));

	/* cPlayerServerCommunication->CallMethod<void, Unity::Vector3*, ERenderDistance>("");
	cClientSend->CallMethod<void, Unity::Vector3*>("PlayerPosition", pos); */

	// Teleport(vec);
	// fnForceMovementUpdate(nullptr);
	// fnPlayerPosition(vec, GetSteamID());
	// G::vPositionOverrideQueue.push_back(new Vector3(vec));
	return fnSendPositionToAll(reinterpret_cast<PlayerServerCommunication_o*>(PlayerServerCommunication), &pos, ERenderDistance::RENDER_FAR);
}

void GameAPI::ForceMovementUpdate() {
	static auto PlayerServerCommunication = FindClassByField("idToDistance", "ForceMovementUpdate");

	static auto fnForceMovementUpdate = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void)>(
			IL2CPP::Class::Utils::GetMethodPointer(PlayerServerCommunication, "ForceMovementUpdate"));

	fnForceMovementUpdate();
}

uint64_t GameAPI::GetSteamID() {
	static uint64_t mySteamID = GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.m_SteamID;
	return mySteamID;
}

Unity::Vector3* GameAPI::GetPlayerCamOffset() {
	auto m_vPlayerPos = Unity::GameObject::Find("Player")->GetTransform()->GetPosition();
	auto curCamPos = reinterpret_cast<Unity::CTransform*>(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerCam)->GetPosition();
	return new Unity::Vector3(m_vPlayerPos.x - curCamPos.x, m_vPlayerPos.y - curCamPos.y, m_vPlayerPos.z - curCamPos.z);
}

void GameAPI::UseItem() {
	static auto cPlayerInventory = GameAPI::FindMethod("LockInventory", 1)->m_pClass;
	static auto fnUseItem = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(PlayerInventory_o*)>(
		IL2CPP::Class::Utils::GetMethodPointer(cPlayerInventory, "UseItem"));
	
	fnUseItem(GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerInventory);
}

EGameModes GameAPI::GetGamemode() {
	return (EGameModes)GameAPI::GetGamemanager()->static_fields->Instance->fields.gameMode->fields.type;
}

void GameAPI::StartGames() {
	static auto fnStartGames = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(GameLoop_o*)>(
		IL2CPP::Class::Utils::GetMethodPointer(reinterpret_cast<Unity::il2cppClass*>(GetGameLoopManager()), "StartGames"));
	fnStartGames(GetGameLoopManager()->static_fields->Instance);
}

void GameAPI::Log(std::string message) {
	GameAPI::AppendMessage(1, IL2CPP::String::New(message), IL2CPP::String::New("[Snowfall]"));
}

void GameAPI::Initialize() {
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

	REGISTER_COMMAND(test);
	REGISTER_COMMAND(profile);
}

Unity::il2cppMethodInfo* GameAPI::FindMethod(const char* methodName, int args) {
	for (size_t i = 0; i < cachedMethods.size(); i++)
		if (!strcmp(methodName, cachedMethods[i]->m_pName) && (args == -1 || cachedMethods[i]->m_uArgsCount == args))
			return cachedMethods[i];
		return nullptr;
}

Unity::il2cppClass* GameAPI::FindClassByField(const char* fieldName, const char* methodName) {
	for (size_t i = 0; i < GameAPI::cachedMethods.size(); i++)
		if (strcmp(methodName, "") == 0 || strcmp(methodName, GameAPI::cachedMethods[i]->m_pName) == 0) {
			auto fields = std::vector<Unity::il2cppFieldInfo*>();
			IL2CPP::Class::FetchFields(GameAPI::cachedMethods[i]->m_pClass, &fields);

			for (size_t x = 0; x < fields.size(); x++)
				if (!strcmp(fieldName, fields[x]->m_pName))
					return fields[x]->m_pParentClass;
		}
	return nullptr;
}

void GameAPI::Prompt(const char* header, const char* content) {
	static auto cPrompt = reinterpret_cast<Unity::CComponent*>(FindMethod("NewPrompt", 2)->m_pClass);

	auto sHeader = IL2CPP::String::New(header);
	auto sContent = IL2CPP::String::New(content);
	
	cPrompt->CallMethodSafe<void*, Unity::System_String*, Unity::System_String*>("NewPrompt", sHeader, sContent);
}

void GameAPI::Alert(const char* content) {
	static auto fnNewAlert = reinterpret_cast<void(__thiscall*)(Alerts_o*, Unity::System_String*, const MethodInfo*)>(
		FindMethod("NewAlert", 1)->m_pMethodPointer);

	Unity::System_String* contentStr = IL2CPP::String::New(content);

	fnNewAlert(GameAPI::GetAlertManager()->static_fields->Instance, contentStr, nullptr);
}

void GameAPI::AppendMessage(uint64_t fromUser, Unity::System_String* message, Unity::System_String* fromUsername) {
	static auto fnAppendMessage = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(Chatbox_o*, uint64_t, Unity::System_String*, Unity::System_String*)>(
		FindMethod("AppendMessage", 3)->m_pMethodPointer);

	fnAppendMessage(GetChatboxManager()->static_fields->Instance, fromUser, message, fromUsername);
}

void GameAPI::SendChatMessage(std::string message) {
	static auto fnSendChatMessage = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(Unity::System_String*)>(
		FindMethod("SendChatMessage", 1)->m_pMethodPointer);

	fnSendChatMessage(IL2CPP::String::New(message));
}

bool GameAPI::Raycast(UnityEngine_Vector3_o origin, UnityEngine_Vector3_o dir, UnityEngine_RaycastHit_o* hitInfo, float maxDistance, int layerMask) {
	static auto Physics = IL2CPP::Class::Find("UnityEngine.Physics");
	void* Raycast = IL2CPP::Class::Utils::GetMethodPointer(Physics, "Raycast", 6);

	static auto raycastMethod = reinterpret_cast<bool(__thiscall*)(UnityEngine_Vector3_o*, UnityEngine_Vector3_o*, UnityEngine_RaycastHit_o*, float, int, int, const MethodInfo*)>(Raycast);
	return raycastMethod(&origin, &dir, hitInfo, maxDistance, layerMask, 0, nullptr);
}

float GameAPI::DeltaTime() {
	static auto Time = IL2CPP::Class::Find("UnityEngine.Time");
	void* deltaTime = IL2CPP::Class::Utils::GetMethodPointer(Time, "get_deltaTime");
	static auto fnGetDeltaTime = reinterpret_cast<float(__thiscall*)(void)>(deltaTime);
	return fnGetDeltaTime();
}

void GameAPI::Teleport(UnityEngine_Vector3_o pos) {
	static auto Physics = IL2CPP::Class::Find("UnityEngine.Physics");
	void* Raycast = IL2CPP::Class::Utils::GetMethodPointer(Physics, "Raycast", 5);
	auto rb = reinterpret_cast<Unity::CRigidbody*>(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerMovement->fields.rb);
	auto enginePos = new Vector3(pos);

	rb->SetVelocity(Unity::Vector3());
	rb->GetMemberValue<Unity::CGameObject*>("gameObject")->GetTransform()->SetPosition(*(enginePos->ToUnity()));
}

CommandResult* Commands::test(const std::vector<std::string>& args) {
	for (const std::string& arg : args) {
		GameAPI::Log("Argument: " + arg);
	}

	CommandResult* result = new CommandResult;
	result->result = true;
	result->error = nullptr;

	return result;
}

CommandResult* Commands::profile(const std::vector<std::string>& args) {
	CommandResult* result = new CommandResult;
	result->error = nullptr;
	result->result = false;

	if (args.size() <= 0) {
		result->error = "Invalid usage: profile <player#>";
		return result;
	}
	
	auto strPlayerId = args.front();
	auto playerId = std::stol(strPlayerId);

	if (playerId == 0) {
		auto err = ("The value \"" + strPlayerId + "\" is not a valid player ID").c_str();
		result->error = err;
		return result;
	}

	auto lookup = GameAPI::GetLobbyManager()->static_fields->Instance->fields.UIDToSteamId;

	if (!lookup->m_Items[playerId-1]) {
		auto err = ("The value \"" + strPlayerId + "\" is not a valid player ID").c_str();
		result->error = err;
		return result;
	}


	GameAPI::Log(std::string("Player SteamID is: " + to_string(lookup->m_Items[playerId - 1])));
	system(std::string("start https://steamcommunity.com/profiles/" + to_string(lookup->m_Items[playerId - 1])).c_str());

	result->result = true;
	return result;
}

//CommandResult* Commands::

int Steamworks::Matchmaking::GetNumLobbyMembers(){//SteamworksNative_CSteamID_o steamId) {
	static auto fnGetNumLobbyMembers = reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(SteamworksNative_CSteamID_o, const MethodInfo*)>(
		MEM::PatternScanRel("GameAssembly.dll", "E8 ? ? ? ? 85 C0 7E 1D", -3));
	return 0;
}
