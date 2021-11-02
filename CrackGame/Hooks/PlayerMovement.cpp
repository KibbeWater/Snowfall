#include "pch.h"

void __stdcall Hook::PlayerMovement::hkPushPlayer(PlayerMovement_o* pThis, UnityEngine_Vector3_o pushForce, const MethodInfo* pMethod)
{
	return;
}

void __stdcall Hook::PlayerMovement::hkJump(PlayerMovement_o* pThis, const MethodInfo* pMethod) 
{
	static auto oJump = static_cast<decltype(&hkJump)>(pJump);

	pThis->fields.grounded = true;

	oJump(pThis, pMethod);
}

void __stdcall Hook::PlayerMovement::hkUpdate(PlayerMovement_o* pThis, const MethodInfo* pMethod)
{
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);

	/*int key = pThis->fields.maxWalkSpeed.fields.currentCryptoKey;
	auto walkSpeed = Obfuscation::DecryptFloat(&pThis->fields.maxWalkSpeed);
	auto newWalkspeed = walkSpeed * 1.25;
	pThis->fields.maxWalkSpeed.fields.fakeValue = Obfuscation::EncryptFloat(newWalkspeed, key);
	auto updatedWalkspeed = Obfuscation::DecryptFloat(&pThis->fields.maxWalkSpeed);*/

	oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerMovement::hkMovement(PlayerMovement_o* pThis, float x, float y, const MethodInfo* pMethod)
{
	static auto oMovement = static_cast<decltype(&hkMovement)>(pMovement);
	
	int SurfaceTypeBackup = pThis->fields.surfaceType;
	pThis->fields.surfaceType = SURFACE_NORMAL;

	if (!Globals::bRedLightFreeze)
		oMovement(pThis, x, y, pMethod);

	pThis->fields.surfaceType = SurfaceTypeBackup;
}
