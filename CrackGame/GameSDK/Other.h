#pragma once

namespace Obfuscation
{
	bool DecryptBool(CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o pThis);
	int DecryptInt(CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o pThis);
	float DecryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* pThis);

	CodeStage_AntiCheat_ObscuredTypes_ObscuredBool_o EncryptBool(bool value, short key);
	CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_o EncryptInt(int value);
	int EncryptFloat(float value, int key);
}

namespace GameAPI {
	void RespawnPlayer(UnityEngine_Vector3_o pos);
	void TagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged);
	void DamagePlayer(long hurtPlayerId, int damage, int itemID, int objectID);
}