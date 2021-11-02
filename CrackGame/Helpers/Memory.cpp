#include "pch.h"

// Pattern scanner to scan 1 module
PVOID MEM::PatternScan(PVOID pModule, const char* szPattern, int iOffset)
{
    // Pattern to bytes
    int PatternBytes[1024];
    uint PatternBytesSize = 0;
    for (char* Current = (const_cast<char*>(szPattern)); Current < (const_cast<char*>(szPattern) + strlen(szPattern)); Current++) {
        if (*Current == '?') {
            ++Current;
            if (*Current == '?')
                ++Current;
            PatternBytes[PatternBytesSize] = -1;
            PatternBytesSize++;
        }
        else {
            PatternBytes[PatternBytesSize] = strtoul(Current, &Current, 16);
            PatternBytesSize++;
        }
    }

    BYTE* ScanAddress = (BYTE*)pModule;
    auto dosHeader = (PIMAGE_DOS_HEADER)ScanAddress;
    auto ntHeaders = (PIMAGE_NT_HEADERS)(ScanAddress + dosHeader->e_lfanew);
    uint ScanSize = ntHeaders->OptionalHeader.SizeOfImage - PatternBytesSize;

    // Scan
    for (uint i = 0; i < ScanSize; i++)
    {
        bool Found = true;
        for (uint j = 0; j < PatternBytesSize; ++j)
        {
            if (ScanAddress[i + j] != PatternBytes[j] && PatternBytes[j] != -1)
            {
                Found = false;
                break;
            }
        }
        if (Found)
            return &ScanAddress[i] + iOffset;
    }

    return nullptr;
}

// Pattern scanner to scan ALL memory
PVOID MEM::PatternScan(const char* szPattern, int iOffset)
{
    MEMORY_BASIC_INFORMATION mbi;
    BYTE* MemoryAddress = (BYTE*)::GetModuleHandleA(NULL);

    // Pattern to bytes
    int PatternBytes[1024];
    uint PatternBytesSize = 0;
    for (char* Current = (const_cast<char*>(szPattern)); Current < (const_cast<char*>(szPattern) + strlen(szPattern)); Current++) {
        if (*Current == '?') {
            ++Current;
            if (*Current == '?')
                ++Current;
            PatternBytes[PatternBytesSize] = -1;
            PatternBytesSize++;
        }
        else {
            PatternBytes[PatternBytesSize] = strtoul(Current, &Current, 16);
            PatternBytesSize++;
        }
    }

    // Search system
    while (true)
    {
        if (!::VirtualQuery(MemoryAddress, &mbi, 0x1000))
            break;

        if (!(mbi.Protect & PAGE_NOACCESS) && !(mbi.Protect & PAGE_GUARD) && !(mbi.State & MEM_FREE) &&
            ((mbi.Protect & PAGE_EXECUTE_READWRITE) || (mbi.Protect & PAGE_EXECUTE_READ) || (mbi.Protect & PAGE_READONLY)))
        {
            LPVOID PageBuffer = VirtualAlloc(nullptr, mbi.RegionSize, MEM_COMMIT, PAGE_READWRITE);
            if (!PageBuffer)
                return nullptr;

            if (memcpy(PageBuffer, mbi.BaseAddress, mbi.RegionSize))
            {
                // Scan
                for (uint i = 0; i < mbi.RegionSize - PatternBytesSize; i++)
                {
                    bool Found = true;
                    for (uint j = 0; j < PatternBytesSize; j++)
                    {
                        if (*(char*)((char*)PageBuffer + i + j) != PatternBytes[j] && PatternBytes[j] != -1)
                        {
                            Found = false;
                            break;
                        }
                    }
                    if (Found)
                    {
                        VirtualFree(PageBuffer, mbi.RegionSize, MEM_FREE);
                        return (PVOID)((INTPTR)mbi.BaseAddress + i + iOffset);
                    }
                }
            }
            ::VirtualFree(PageBuffer, mbi.RegionSize, MEM_FREE);
        }

        MemoryAddress += mbi.RegionSize;
    }

    return nullptr;
}

// Pattern scanner dynamic, but bad secure bc string based module
PVOID MEM::PatternScan(const char* szModule, const char* szPattern, int iOffset)
{
    if (!szModule)
        return PatternScan(szPattern, iOffset);

    BYTE* Module = (BYTE*)::GetModuleHandleA(szModule);
    if (!Module)
        return PatternScan(szPattern, iOffset);

    // Pattern to bytes
    int PatternBytes[1024];
    uint PatternBytesSize = 0;
    for (char* Current = (const_cast<char*>(szPattern)); Current < (const_cast<char*>(szPattern) + strlen(szPattern)); Current++) {
        if (*Current == '?') {
            ++Current;
            if (*Current == '?')
                ++Current;
            PatternBytes[PatternBytesSize] = -1;
            PatternBytesSize++;
        }
        else {
            PatternBytes[PatternBytesSize] = strtoul(Current, &Current, 16);
            PatternBytesSize++;
        }
    }

    BYTE* ScanAddress = (BYTE*)Module;
    auto dosHeader = (PIMAGE_DOS_HEADER)ScanAddress;
    auto ntHeaders = (PIMAGE_NT_HEADERS)(ScanAddress + dosHeader->e_lfanew);
    uint ScanSize = ntHeaders->OptionalHeader.SizeOfImage - PatternBytesSize;

    // Scan
    for (uint i = 0; i < ScanSize; i++)
    {
        bool Found = true;
        for (uint j = 0; j < PatternBytesSize; ++j)
        {
            if (ScanAddress[i + j] != PatternBytes[j] && PatternBytes[j] != -1)
            {
                Found = false;
                break;
            }
        }
        if (Found)
            return &ScanAddress[i] + iOffset;
    }

    return nullptr;
}

PVOID MEM::FromRelative(PVOID pAddress)
{
    return (PVOID)((INTPTR)pAddress + 4 + *(DWORD*)(pAddress));
}

PVOID MEM::PatternScanRel(const char* szModule, const char* szPattern, int iOffset)
{
    PVOID Address = PatternScan(szModule, szPattern, iOffset);
    if (!Address)
        return nullptr;

    return FromRelative(Address);
}