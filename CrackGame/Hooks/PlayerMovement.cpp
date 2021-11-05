#include "pch.h"

void __stdcall Hook::PlayerMovement::hkPushPlayer(PlayerMovement_o* pThis, UnityEngine_Vector3_o pushForce, const MethodInfo* pMethod)
{
	return;
}

void __stdcall Hook::PlayerMovement::hkJump(PlayerMovement_o* pThis, const MethodInfo* pMethod) 
{
	static auto oJump = static_cast<decltype(&hkJump)>(pJump);

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

	Obfuscation::EncryptFloat(&pThis->fields.defaultMoveSpeed, originalDefaultSpeed * 2.5);
	Obfuscation::EncryptFloat(&pThis->fields.maxWalkSpeed, originalWalkSpeed * 2.5);
	Obfuscation::EncryptFloat(&pThis->fields.maxRunSpeed, originalRunSpeed * 2.5);
	Obfuscation::EncryptFloat(&pThis->fields.maxSpeed, 1000);

	oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerMovement::hkMovement(PlayerMovement_o* pThis, float x, float y, const MethodInfo* pMethod)
{
	static auto oMovement = static_cast<decltype(&hkMovement)>(pMovement);
	
	int oldSurfaceType = pThis->fields.surfaceType;
	pThis->fields.surfaceType = SURFACE_NORMAL;

	oMovement(pThis, x, y, pMethod);

	pThis->fields.surfaceType = oldSurfaceType;
}
