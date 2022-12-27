#include "pch.h"
#include "proc.h"
#include "mem.h"
#include "offsets.h"
#include "newVal.h"

int main()
{
	HANDLE console_color{};
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 14);

	DWORD PID = GetProcID(L"ac_client.exe");
	HANDLE hProc{};

	uintptr_t modBaseAddr{};
	uintptr_t localPlayerAddr{};

	if (PID)
	{
		hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);

		modBaseAddr = GetModuleBaseAddr(PID, L"ac_client.exe");

		localPlayerAddr = modBaseAddr + 0x10f4f4;
	}
	else
	{
		std::cout << "Process not found" << "\n";
		std::getchar();
		return 0;
	}
	// Info
	std::cout << "PID: " << PID << "\n";
	std::cout << std::hex;
	std::cout << "MBA: " << modBaseAddr << "\n";

	// Foo
	bool bAmmo{}, bHealth{}, bGrenade{};

	// Resolve pointers
	uintptr_t healthAddr = FindDMAAddy(hProc, localPlayerAddr, localPlayer::health);
	uintptr_t armorAddr = FindDMAAddy(hProc, localPlayerAddr, localPlayer::armor);
	//uintptr_t ammoAddr = FindDMAAddy(hProc, localPlayerAddr, localPlayer::currentAmmo);

	// Menu
	SetConsoleTextAttribute(console_color, 12);

	std::cout << "\n";
	std::cout << "Dulge External Trainer" << "\n";
	std::cout << "\n";
	std::cout << "[ F1 ]" << "\t" << "GODMODE" << "\n";
	std::cout << "[ F2 ]" << "\t" << "UNLIMITED AMMO" << "\n";
	std::cout << "[ F3 ]" << "\t" << "UNLIMITED GRENADE" << "\n";

	// Main hack loop
	DWORD dwExit = 0;
	while (GetExitCodeProcess(hProc, &dwExit) && dwExit == STILL_ACTIVE)
	{
		// Godmode
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			bHealth = !bHealth;
		}

		// Godmode
		if (bHealth)
		{
			mem::PatchEx((BYTE*)healthAddr, (BYTE*)&godmode::health, sizeof(godmode::health), hProc);
			mem::PatchEx((BYTE*)armorAddr, (BYTE*)&godmode::armor, sizeof(godmode::armor), hProc);
		}

		// inc ammo
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bAmmo = !bAmmo;

			if (bAmmo)
			{
				mem::PatchEx((BYTE*)(modBaseAddr + 0x637e9), (BYTE*)"\xFF\x06", 2, hProc);
			}
			else
			{
				mem::PatchEx((BYTE*)(modBaseAddr + 0x637e9), (BYTE*)"\xFF\x0E", 2, hProc);
			}
		}

		// inc grendade
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			bGrenade = !bGrenade;

			if (bGrenade)
			{
				mem::PatchEx((BYTE*)(modBaseAddr + 0x63378), (BYTE*)"\xFF\x00", 2, hProc);
			}
			else
			{
				mem::PatchEx((BYTE*)(modBaseAddr + 0x63378), (BYTE*)"\xFF\x08", 2, hProc);
			}
		}

		Sleep(10);
	}


	std::cout << "Process not found" << "\n";
	std::getchar();
	return 0;
}