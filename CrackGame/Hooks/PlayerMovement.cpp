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

	if (F::bAirJump) {
		pThis->fields.grounded = true;
		//Obfuscation::EncryptBool(&pThis->fields.readyToJump, true);
	}

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
		static float speed = 30;
		static float speedFast = 50;


		auto curCam = Unity::Camera::GetMain();
		auto curPos = curCam->GetTransform()->GetPosition(); // Initialize curPos without creating a new Vector3
		auto fwd = new Vector3(curCam->GetMemberValue<Unity::Vector3>("forward"));
		auto right = new Vector3(curCam->GetMemberValue<Unity::Vector3>("right"));
		static auto playerCamOffset = Vector3(*GameAPI::GetPlayerCamOffset());
		auto deltaTime = GameAPI::DeltaTime();

		Vector3 tpPos = curPos; // Initialize tpPos with curPos

		auto curSpeed = speedFast;

		if (GetAsyncKeyState(0x57) & 0x8000) // W
			tpPos += (*fwd) * (deltaTime * curSpeed);
		if (GetAsyncKeyState(0x53) & 0x8000) // S
			tpPos -= (*fwd) * (deltaTime * curSpeed);

		if (GetAsyncKeyState(0x44) & 0x8000) // D
			tpPos += (*right) * (deltaTime * curSpeed);
		if (GetAsyncKeyState(0x41) & 0x8000) // A
			tpPos -= (*right) * (deltaTime * curSpeed);

		GameAPI::Teleport((tpPos + playerCamOffset).ToEngine());
	}
}
