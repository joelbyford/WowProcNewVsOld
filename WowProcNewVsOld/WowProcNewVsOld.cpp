// WowProcNewVsOld.cpp : Simple app to show the different return values of IsWow64Process vs. IsWow64Process2 on ARM64
//

#include <iostream>
#include <windows.h>
#include <tchar.h>

typedef BOOL(__stdcall *PISWOW64PROCESS)(
	HANDLE hProcess,
	PBOOL Wow64Process
	);

typedef BOOL(__stdcall *PISWOW64PROCESS2)(
	HANDLE hProcess,
	USHORT *pProcessMachine,
	USHORT *pNativeMachine
	);



int main()
{
	PISWOW64PROCESS		pIsWow64Process = NULL;
	PISWOW64PROCESS2	pIsWow64Process2 = NULL;
	BOOL				isWow64Old = FALSE;
	BOOL				isWow64New = FALSE;
	USHORT				pProcessMachine = 0;
	USHORT				pNativeMachine = 0;


	//Get Values from Old Version
	pIsWow64Process = (PISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "IsWow64Process");
	if (pIsWow64Process) {
		pIsWow64Process(GetCurrentProcess(), &isWow64Old);
	}

	//Get Values from New Version
	pIsWow64Process2 = (PISWOW64PROCESS2)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "IsWow64Process2");
	if (pIsWow64Process2) {
		isWow64New = pIsWow64Process2(GetCurrentProcess(), &pProcessMachine, &pNativeMachine);
	}

	printf("---------------------------------------------\n");

	// Running in emulation, output what's being reported
	printf("Old Boolean: %i\n", isWow64Old);
	printf("---------------------------------------------\n");
	printf("Native Machine Architecture: 0x%.4X \n", pNativeMachine);
	printf("Process Machine Architecture: 0x%.4X \n", pProcessMachine);
	printf("New Boolean: %i\n", isWow64New);

    printf("---------------------------------------------\n");
	printf("Please See the following for list of machine constants.:\n");
	printf("https://docs.microsoft.com/en-us/windows/win32/sysinfo/image-file-machine-constants \n");

}

