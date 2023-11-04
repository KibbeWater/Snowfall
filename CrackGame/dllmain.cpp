#include "pch.h"

void Started() {
    GameAPI::Prompt("Snowfall", "Hooked and ready for use!");
}

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
    IL2CPP::Initialize();
    GameAPI::Initialize();

    Steamworks::Matchmaking::GetNumLobbyMembers();

    if (!Hook::Init())
        ::MessageBoxA(0, "Failed to initialize all hooks", "ERROR", MB_OK);
    ImplHookDX11_Init((HMODULE)lpParameter, FindWindow(0, L"Crab Game"));

    // GameAPI::Prompt("Snowfall", "Hooked and ready for use!"); //IL2CPP::Thread::Create(Started);

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

