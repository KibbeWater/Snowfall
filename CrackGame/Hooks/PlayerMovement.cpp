#include "pch.h"

void __stdcall Hook::PlayerMovement::hkPushPlayer(PlayerMovement_o* pThis, UnityEngine_Vector3_o pushForce, const MethodInfo* pMethod)
{
	static auto oPushPlayer = static_cast<decltype(&hkPushPlayer)>(pPushPlayer);
	
	if (!F::bAntiKnockback)
		oPushPlayer(pThis, pushForce, pMethod);
}

void __stdcall Hook::PlayerMovement::hkJump(PlayerMovement_o* pThis, const MethodInfo* pMethod) 
{
	static auto oJump = static_cast<decltype(&hkJump)>(pJump);

	if (F::bAirJump)
		pThis->fields.grounded = true;
	//Obfuscation::EncryptBool(&pThis->fields.readyToJump, true);

	oJump(pThis, pMethod);
}

void __stdcall Hook::PlayerMovement::hkUpdate(PlayerMovement_o* pThis, const MethodInfo* pMethod)
{
	static auto oUpdate = static_cast<decltype(&hkUpdate)>(pUpdate);

	static int originalDefaultSpeed = Obfuscation::DecryptFloat(&pThis->fields.defaultMoveSpeed);
	static int originalWalkSpeed = Obfuscation::DecryptFloat(&pThis->fields.maxWalkSpeed);
	static int originalRunSpeed = Obfuscation::DecryptFloat(&pThis->fields.maxRunSpeed);
	static int originalMax = Obfuscation::DecryptFloat(&pThis->fields.maxSpeed);

	float increasePercent = F::bSpeedhack ? (float)F::iSpeedPercent / 100 : 1;

	Obfuscation::EncryptFloat(&pThis->fields.defaultMoveSpeed, originalDefaultSpeed * increasePercent);
	Obfuscation::EncryptFloat(&pThis->fields.maxWalkSpeed, originalWalkSpeed * increasePercent);
	Obfuscation::EncryptFloat(&pThis->fields.maxRunSpeed, originalRunSpeed * increasePercent);
	Obfuscation::EncryptFloat(&pThis->fields.maxSpeed, originalMax * increasePercent);

	if (F::bDisablePregameFreeze)
		GameAPI::GetPersistentData()->static_fields->frozen = false;

	oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerMovement::hkMovement(PlayerMovement_o* pThis, float x, float y, const MethodInfo* pMethod)
{
	static auto oMovement = static_cast<decltype(&hkMovement)>(pMovement);
	
	int oldSurfaceType = pThis->fields.surfaceType;
	if (F::bNoSlide)
		pThis->fields.surfaceType = SURFACE_NORMAL;

	oMovement(pThis, x, y, pMethod);

	pThis->fields.surfaceType = oldSurfaceType;
}
