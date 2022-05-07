#include "pch.h"
#include ".\Packet Capture/MyWinDivert.h"
#include ".\Damage Meter/Damage Meter.h"
#include ".\UI\UiWindow.h"
#include ".\Damage Meter\MySQLite.h"
#include <shellapi.h>

#pragma locale ("Korean")

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )
#endif

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) 
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR szCmdLine, _In_ int iCmdShow) {
	int argc;
	LPWSTR* argv;
	argv = CommandLineToArgvW(GetCommandLine(),&argc);
	if (argc == 2)
	{
		if (wcscmp(argv[1], L"log") == 0)
		{
			LogInstance.Enable();
		}
	}
	_wsetlocale(LC_ALL, L"Korean");
	MiniDump::Begin();

	if (!SWDB.Init()) {
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("InitDB Failed")));
		exit(-1);
	}

	if (WINDIVERT.Init()) {
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("Init Module Listener Failed")));
		exit(-1);
	}

	if (UIWINDOW.Init(1, 1, 1, 1)) {
		UIWINDOW.Run();
	}
	else {
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("Init UIWINDOW Failed")));
	}

	MiniDump::End();
}