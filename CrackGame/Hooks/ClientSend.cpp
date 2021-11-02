#include "pch.h"

void __stdcall Hook::ClientSend::hkPlayerPosition(UnityEngine_Vector3_o position, uint64_t toId, const MethodInfo* pMethod)
{
	static auto oPlayerPosition = static_cast<decltype(&hkPlayerPosition)>(pPlayerPosition);

	if (!G::bRedLightFreeze)
		oPlayerPosition(position, toId, pMethod);
}

void __stdcall Hook::ClientSend::hkPlayerRotation(float x, float y, uint64_t toId, const MethodInfo* pMethod)
{
	static auto oPlayerRotation = static_cast<decltype(&hkPlayerRotation)>(pPlayerRotation);

	if (!G::bRedLightFreeze)
		oPlayerRotation(x, y, toId, pMethod);
}
