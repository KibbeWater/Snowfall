#pragma once

#define DO_HOOK(FuncAdr, Class, Function) if (MH_CreateHook(FuncAdr, &##Class##::hk##Function##, &##Class##::p##Function##) != MH_OK) { if(DEV_MODE) DebugBreak(); return false; }
#define HOOK_ORIG_FUNC(Function) static_cast<decltype(&hk##Function##)>(p##Function##)

#define HOOK_DEF(Function, ReturnType, ...) \
    inline void* p##Function; \
    ReturnType __stdcall hk##Function(__VA_ARGS__, const MethodInfo* pMethod);

namespace Hook
{
	extern INL bool Init();
	extern INL bool Shutdown();
}