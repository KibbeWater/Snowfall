#include "pch.h"

void __stdcall Hook::GamemodeBombTag::hkTagPlayer(GameModeBombTag_o* pThis, long tagger, long tagged, const MethodInfo* pMethod)
{
	static auto oTagPlayer = static_cast<decltype(&hkTagPlayer)>(pTagPlayer);

	oTagPlayer(pThis, tagger, tagged, pMethod);
	
	if (!G::pPlayerManager)
		if (G::pPlayerManager->fields.steamProfile.fields.Id.fields.Value == tagged && F::bBombDeleting)
			oTagPlayer(pThis, tagged, tagger, pMethod);
}
