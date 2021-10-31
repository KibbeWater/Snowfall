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

	return;
}
