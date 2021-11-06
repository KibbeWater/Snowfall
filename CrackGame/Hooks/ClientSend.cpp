#include "pch.h"

void __stdcall Hook::ClientSend::hkPlayerPosition(UnityEngine_Vector3_o position, uint64_t toId, const MethodInfo* pMethod)
{
	static auto oPlayerPosition = static_cast<decltype(&hkPlayerPosition)>(pPlayerPosition);

	if (!(G::bRedLightFreeze && F::bRedGreenProtection) || !F::bRedGreenProtection)
		oPlayerPosition(position, toId, pMethod);
}

void __stdcall Hook::ClientSend::hkPlayerRotation(float x, float y, uint64_t toId, const MethodInfo* pMethod)
{
	static auto oPlayerRotation = static_cast<decltype(&hkPlayerRotation)>(pPlayerRotation);

	if (!(G::bRedLightFreeze && F::bRedGreenProtection) || !F::bRedGreenProtection)
		oPlayerRotation(x, y, toId, pMethod);
}

void __stdcall Hook::ClientSend::hkDamagePlayer(long hurtPlayerId, int damage, UnityEngine_Vector3_o* damageDir, int itemID, int objectID, const MethodInfo* pMethod)
{
	static auto oDamagePlayer = static_cast<decltype(&hkDamagePlayer)>(pDamagePlayer);

	if (G::bAnticheatDisabler && (itemID == WEAPON_RIFLE || itemID == WEAPON_SHOTGUN))
		return;

	oDamagePlayer(hurtPlayerId, damage, damageDir, itemID, objectID, pMethod);
}

void __stdcall Hook::ClientSend::hkUseItem(int itemID, UnityEngine_Vector3_o* dir, const MethodInfo* pMethod)
{
	static auto oUseItem = static_cast<decltype(&hkUseItem)>(pUseItem);

	if (G::bAnticheatDisabler && (itemID == WEAPON_RIFLE || itemID == WEAPON_SHOTGUN))
		return;

	oUseItem(itemID, dir, pMethod);
}
