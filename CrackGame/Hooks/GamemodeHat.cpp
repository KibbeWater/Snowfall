#include "pch.h"

void __stdcall Hook::GamemodeHat::hkStealHat(GameModeHat_o* pThis, long stealer, long stolenFrom, const MethodInfo* pMethod)
{
	static auto oStealHat = static_cast<decltype(&hkStealHat)>(pStealHat);

	oStealHat(pThis, stealer, stolenFrom, pMethod);

	auto rot = new Vector3(1,1,1);
	static long yourSteamID = GameAPI::GetSteamID();
	if (F::bAntiBombTag)
		GameAPI::PunchPlayer(stealer, rot->ToEngine());
}
