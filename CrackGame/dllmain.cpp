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
        MessageBox(0, L"Failed to initialize all hooks", L"ERROR", MB_OK);
    else
        MessageBox(0, L"Initialized hooks!", L"Success", MB_OK);

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

