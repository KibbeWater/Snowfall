#pragma once

struct CommandResult;
enum ELockState;

#define DEF_COMMAND(CommandName) CommandResult* ##CommandName##(const std::vector<std::string>& args);
#define REGISTER_COMMAND(CommandName) G::commandHandler->RegisterCommand(#CommandName, &Commands::##CommandName##);

namespace Obfuscation
{
	bool DecryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o pThis);
	int DecryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o pThis);
	float DecryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* pThis);

	void EncryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o* obscuredBool, bool value);
	void EncryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o* obscuredInt, int value);
	void EncryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* obscuredFloat, float value);
}

namespace Packet {
	long ReadLong(Packet_o* packet);
	float ReadFloat(Packet_o* packet);
	Vector3 ReadVector3(Packet_o* packet);
	void ResetPacket(Packet_o* packet);
}

namespace GameAPI {
	inline std::vector<Unity::il2cppMethodInfo*> cachedMethods = std::vector<Unity::il2cppMethodInfo*>();

	// Managers
	GameManager_c* GetGamemanager();
	PlayerServerCommunication_c* GetServerCommunicator();
	SteamManager_c* GetSteammanager();
	PersistentPlayerData_c* GetPersistentData();
	PlayerInventory_c* GetInventory();
	ItemManager_c* GetItemMgr();
	PlayerInput_c* GetPlayerInput();
	LobbyManager_c* GetLobbyManager();
	GameLoop_c* GetGameLoopManager();
	Prompt_c* GetPromptManager();
	Alerts_c* GetAlertManager();
	Chatbox_c* GetChatboxManager();
	QuestManager_c* GetQuestManager();
	SaveManager_c* GetSaveManager();
	
	// In-Game API
	void Respawn(int64 playerId);
	void TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged);
	void DamagePlayer(unsigned long hurtPlayerId, int damage, UnityEngine_Vector3_o dmgDir, int itemID, int objectID);
	void PunchPlayer(unsigned long punchTargetId, UnityEngine_Vector3_o dmgDir);
	ItemData_o* GetItemByID(int ID);
	void ForceGiveItem(ItemData_o* item) noexcept;
	ItemData_o* LobbyGiveWeapon(int64 clientId, EWeapons itemId);
	bool LobbyGiveAllWeapon(EWeapons itemId);
	void BanPlayer(long ID);
	bool TrySnowballReload();
	void BreakAll();
	void TakeAllTiles();
	void DropItem(int slot = -1);
	std::vector<ItemData_o*> GetItems();
	ItemData_o* FindItemById(int itemId);
	std::vector<PlayerManager_o*> GetPlayers();
	std::vector<PlayerManager_o*> GetPlayersAlive();
	std::vector<PlayerManager_o*> GetPlayersDead();
	
	// CrackGame API
	void Initialize();
	Unity::il2cppMethodInfo* FindMethod(const char* methodName, int args = -1);
	Unity::il2cppClass* FindClassByField(const char* fieldName, const char* methodName = "");

	void Prompt(const char* header, const char* content);
	void Alert(const char* content);
	void AppendMessage(uint64_t fromUser, Unity::System_String* message, Unity::System_String* fromUsername);
	void SendChatMessage(std::string message);
	void Teleport(UnityEngine_Vector3_o pos);
	int ResolvePlayer(std::string resolvable);
	int64 ResolvePlayer64(std::string resolvable);
	std::vector<std::tuple<int, SteamworksNative_CSteamID_o>>* GetLobbyMembers();
	void CompleteDaily();
	void CSendPosition(UnityEngine_Vector3_o* vec);
	void ForceMovementUpdate();
	uint64_t GetSteamID();
	bool IsLobbyOwner();
	Unity::Vector3* GetPlayerCamOffset();
	void UseItem();
	EGameModes GetGamemode();
	void StartGames();
	void Log(std::string message);

	// Data folders
	std::string GetAppDataPath();
	std::string GetDataPath();
	std::string GetLuaPath();

	// Unity game functions
	bool Raycast(UnityEngine_Vector3_o origin, UnityEngine_Vector3_o dir, UnityEngine_RaycastHit_o* hitInfo, float maxDistance, int layerMask);
	float DeltaTime();
	
	void SetLockState(ELockState lockState);
	ELockState GetLockState();
}

namespace Steamworks {
	namespace Matchmaking {
		int GetNumLobbyMembers();//SteamworksNative_CSteamID_o steamId);
		SteamworksNative_CSteamID_o GetLobbyMemberByIndex(int iMember);
	}
}

namespace Commands {
	DEF_COMMAND(test);
	DEF_COMMAND(profile);

	DEF_COMMAND(give);

	DEF_COMMAND(respawn)
}