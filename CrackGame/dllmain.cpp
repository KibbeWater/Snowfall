#include "pch.h"

INL bool IsShutdown(LPVOID lpParameter)
{
    // Temp solution
    return false;

    //if (!InputSys::IsKeyDown(VK_END))
    //    return false;

    Hook::Shutdown();

    ::FreeLibraryAndExitThread((HMODULE)lpParameter, 1);

    return true;
}

DWORD WINAPI OnDllAttach(LPVOID lpParameter)
{
    if (!Hook::Init())
        ::MessageBoxA(0, "Failed to initialize all hooks", "ERROR", MB_OK);
    else
        ::MessageBoxA(0, "Initialized hooks!", "Success", MB_OK);

    while (true)
    {
        if (IsShutdown(lpParameter))
            break;

        ::Sleep(100);
    }

    return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            float* pReachAccessPoint = (float*)MEM::RelativeScan("GameAssembly.dll", "F3 0F 10 15 ? ? ? ? 48 8D 55 FF", 4);

            float Value = *pReachAccessPoint;

            ::FreeLibraryAndExitThread((HMODULE)hModule, 1);








            ::DisableThreadLibraryCalls(hModule);
            ::CreateThread(NULL, 0, OnDllAttach, hModule, NULL, nullptr);
        }
        break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        {
        }
        break;
    }
    return TRUE;
}

