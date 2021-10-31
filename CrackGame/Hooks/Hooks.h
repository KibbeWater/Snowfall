#pragma once

#define DO_HOOK(FuncAdr, Class, Function) if (MH_CreateHook(FuncAdr, &##Class##::hk##Function##, &##Class##::p##Function##) != MH_OK) return false;

namespace Hook
{
	extern INL MH_STATUS Do(void* pTargetFn, void* pDetourFn, void** pOriginalFn);
	extern INL MH_STATUS UnDoAll();

	extern INL bool Init();
}