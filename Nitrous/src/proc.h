#pragma once

#include "pch.h"

uintptr_t GetProcID(const wchar_t* procName);

uintptr_t GetModuleBaseAddr(DWORD proId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

