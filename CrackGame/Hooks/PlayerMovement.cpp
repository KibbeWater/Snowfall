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

	oUpdate(pThis, pMethod);
}

void __stdcall Hook::PlayerMovement::hkMovement(PlayerMovement_o* pThis, float x, float y, const MethodInfo* pMethod)
{
	static auto oMovement = static_cast<decltype(&hkMovement)>(pMovement);

	if (!F::bFly) {
		static int originalDefaultSpeed = Obfuscation::DecryptFloat(&pThis->fields.defaultMoveSpeed);
		static int originalWalkSpeed = Obfuscation::DecryptFloat(&pThis->fields.maxWalkSpeed);
		static int originalRunSpeed = Obfuscation::DecryptFloat(&pThis->fields.maxRunSpeed);
		static int originalMax = Obfuscation::DecryptFloat(&pThis->fields.maxSpeed);

		float increasePercent = F::bSpeedhack ? (float)F::iSpeedPercent / 100 : 1;

		Obfuscation::EncryptFloat(&pThis->fields.defaultMoveSpeed, originalDefaultSpeed * increasePercent);
		Obfuscation::EncryptFloat(&pThis->fields.maxWalkSpeed, originalWalkSpeed * increasePercent);
		Obfuscation::EncryptFloat(&pThis->fields.maxRunSpeed, originalRunSpeed * increasePercent);
		Obfuscation::EncryptFloat(&pThis->fields.maxSpeed, originalMax * increasePercent);

		int oldSurfaceType = pThis->fields.surfaceType;
		if (F::bNoSlide)
			pThis->fields.surfaceType = SURFACE_NORMAL;

		oMovement(pThis, x, y, pMethod);

		pThis->fields.surfaceType = oldSurfaceType;
	} else {
		static float speed = 5;

		auto input = GameAPI::GetPlayerInput();
		auto curPos = Vector3(GameAPI::GetPosition(input->static_fields->_Instance_k__BackingField->fields.playerCam));
		auto fwd = Vector3(GameAPI::GetForward(input->static_fields->_Instance_k__BackingField->fields.playerCam));
		auto right = Vector3(GameAPI::GetRight(input->static_fields->_Instance_k__BackingField->fields.playerCam));
		auto deltaTime = GameAPI::DeltaTime();

		if (GetAsyncKeyState(0x57) & 0x01) // W
			curPos += fwd * deltaTime * speed;
		if (GetAsyncKeyState(0x53) & 0x01) // S
			curPos += (fwd * -1)* deltaTime * speed;

		if (GetAsyncKeyState(0x44) & 0x01) // D
			curPos += right * deltaTime * speed;
		if (GetAsyncKeyState(0x41) & 0x01) // A
			curPos += (right * -1) * deltaTime * speed;

		GameAPI::Teleport(curPos.ToUnity());
	}
}
