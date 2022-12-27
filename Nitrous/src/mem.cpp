#include "pch.h"
#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc)
{
	DWORD oldProctect{};
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldProctect);
	WriteProcessMemory(hProc, dst, src, size, nullptr);
	VirtualProtectEx(hProc, dst, size, oldProctect, &oldProctect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProc)
{
	BYTE* nopArray = new BYTE[size];
	memset(dst, 0x90, size);

	PatchEx(dst, nopArray, size, hProc);
	delete[] nopArray;
}