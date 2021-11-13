#pragma once
enum ELockState;

namespace Obfuscation
{
	bool DecryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o pThis);
	int DecryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o pThis);
	float DecryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* pThis);

	void EncryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o* obscuredBool, bool value);
	void EncryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o* obscuredInt, int value);
	void EncryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* obscuredFloat, float value);
}

namespace GameAPI {
	GameManager_c* GetGamemanager();
	SteamManager_c* GetSteammanager();
	PersistentPlayerData_c* GetPersistentData();
	PlayerInventory_c* GetInventory();
	ItemManager_c* GetItemMgr();
	PlayerInput_c* GetPlayerInput();
	LobbyManager_c* GetLobbyManager();
	Prompt_c* GetPromptManager();

	void SetLockState(ELockState lockState);
	ELockState GetLockState();

	void RespawnPlayer(UnityEngine_Vector3_o pos);
	void TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged);
	void DamagePlayer(long hurtPlayerId, int damage, int itemID, int objectID, UnityEngine_Vector3_o dmgDir = {});
	ItemData_o* GetItemByID(int ID);
	void ForceGiveItem(ItemData_o* item) noexcept;
	void SendPacket(Packet_o* packet);
	void BanPlayer(long ID);
	void JoinLobby(long ID);
	void Prompt(const char* header, const char* content);
	bool Raycast(UnityEngine_Vector3_o origin, UnityEngine_Vector3_o dir, UnityEngine_RaycastHit_o* hitInfo, float maxDistance, int layerMask);
	UnityEngine_Vector3_o GetPosition(UnityEngine_Transform_o* pThis);
	UnityEngine_Vector3_o GetForward(UnityEngine_Transform_o* pThis);
	void Teleport(UnityEngine_Vector3_o pos);
}