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

	void SetLockState(ELockState lockState);
	ELockState GetLockState();

	void RespawnPlayer(UnityEngine_Vector3_o pos);
	void TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged);
	void DamagePlayer(long hurtPlayerId, int damage, int itemID, int objectID, UnityEngine_Vector3_o dmgDir = {});
	ItemData_o* GetItemByID(int ID);
	void ForceGiveItem(ItemData_o* item);
	void SendPacket(Packet_o* packet);
}