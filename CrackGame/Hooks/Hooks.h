#pragma once

#define DO_HOOK(FuncAdr, Class, Function) if (MH_CreateHook(FuncAdr, &##Class##::hk##Function##, &##Class##::p##Function##) != MH_OK) return false;

namespace Hook
{
	extern INL bool Init();
	extern INL bool Shutdown();
}