#pragma once

namespace MEM
{
    PVOID PatternScan(PVOID pModule, const char* szPattern, int iOffset = 0); // Pattern scanner to scan 1 module
    PVOID PatternScan(const char* szPattern, int iOffset = 0); // Pattern scanner to scan ALL memory
    PVOID PatternScan(const char* szModule, const char* szPattern, int iOffset = 0); // Pattern scanner dynamic, but bad secure bc string based module

    PVOID FromRelative(PVOID pAddress); // Address to relative convert to absoulte address
    PVOID PatternScanRel(const char* szModule, const char* szPattern, int iOffset = 0); // Relative pattern scan
}