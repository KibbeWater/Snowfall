#include "pch.h"

float AntiCheat::DecryptFloat(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o* pThis, const MethodInfo* pMethod)
{
	static auto fnDecryptFloat = reinterpret_cast<float(__thiscall*)(CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_o*, const MethodInfo*)>(
		MEM::PatternScan("GameAssembly.dll", "33 D2 E9 ? ? ? ? CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 20 80 79 0C 00 48 8B FA 48 8B D9 75 28"));

	return fnDecryptFloat(pThis, pMethod);
}

