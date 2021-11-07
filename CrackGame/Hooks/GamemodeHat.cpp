#include "pch.h"

void __stdcall Hook::GamemodeHat::hkStealHat(GameModeHat_o* pThis, uint64_t stealer, uint64_t stolenFrom, const MethodInfo* pMethod)
{
	static auto oStealHat = static_cast<decltype(&hkStealHat)>(pStealHat);

	oStealHat(pThis, stealer, stolenFrom, pMethod);

	static long myID = GameAPI::GetSteammanager()->static_fields->Instance->fields._PlayerSteamId_k__BackingField.fields.m_SteamID;
	if (stolenFrom == myID) {
		OutputDebugString(L"It was mine!\n");
	}
}
