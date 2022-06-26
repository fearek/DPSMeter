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
void getconfig(CSimpleIniA& ini, int sec)
{
	if (sec == 1) //meter
	{
		bool shouldLog = ini.GetBoolValue("Meter","LogFile",false);
		if (shouldLog)
		{
			LogInstance.Enable();
		}
		long language = ini.GetLongValue("Meter", "Language", 0);
		Language.SetLanguage(LANGUAGE(language));
		bool shouldLogMonsterStats = ini.GetBoolValue("Meter","LogMonsterStats",true);
		const char* font = ini.GetValue("Meter","DefaultFont");
		if (font)
		{
			DAMAGEMETER.selectedFont.filename = font;
			DAMAGEMETER.selectedFont.path = font;
		}
		DAMAGEMETER.shouldLogMstrStats = shouldLogMonsterStats;
		return;
	}
}
bool configloaded = false;
bool savefont()
{
	DAMAGEMETER.ini.SetValue("Meter", "DefaultFont", DAMAGEMETER.selectedFont.path.c_str());
	SI_Error rc = DAMAGEMETER.ini.SaveFile("meterconfig.ini");
	if (rc < 0) {
		MessageBoxA(NULL, "Something is wrong with your system, cant make config file.", "ERROR", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}
bool createconfig()
{
	DAMAGEMETER.ini.SetBoolValue("Loader", "XignCheck", true);
	DAMAGEMETER.ini.SetBoolValue("Loader", "OpenMeterOnInjection", true);
	DAMAGEMETER.ini.SetLongValue("Meter", "Language", 0);
	DAMAGEMETER.ini.SetBoolValue("Meter", "LogFile", false);
	DAMAGEMETER.ini.SetBoolValue("Meter", "LogMonsterStats",true);
	DAMAGEMETER.ini.SetValue("Meter", "DefaultFont","");
	SI_Error rc = DAMAGEMETER.ini.SaveFile("meterconfig.ini");
	if (rc < 0) {
		MessageBoxA(NULL,"Something is wrong with your system, cant make config file.","ERROR", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}
void loadconfig()
{
	DAMAGEMETER.ini.SetUnicode();
	SI_Error rc = DAMAGEMETER.ini.LoadFile("meterconfig.ini");
	if (rc < 0)
	{
		bool test = createconfig();
		if (test == false) return;
	}
	SI_Error rc2 = DAMAGEMETER.ini.LoadFile("meterconfig.ini");
	if (rc2 < 0)
	{
		MessageBoxA(NULL,"Loading config failed for some reason?","ERROR", MB_OK | MB_ICONERROR);
		return;
	}
	configloaded = true;
	CSimpleIniA::TNamesDepend sections;
	CSimpleIniA::TNamesDepend::const_iterator it;
	DAMAGEMETER.ini.GetAllSections(sections);
	for (it = sections.begin(); it != sections.end(); ++it)
	{
		if (!std::strcmp(it->pItem, "Meter"))
		{
			getconfig(DAMAGEMETER.ini, 1);
		}
	}
	return;
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR szCmdLine, _In_ int iCmdShow) {
	//ParseCommandLineArguments();
	loadconfig();
	_wsetlocale(LC_ALL, L"Korean");
	MiniDump::Begin();

	if (!SWDB.Init()) {
		LogInstance.WriteLog("InitDB Failed");
		exit(-1);
	}

	if (WINDIVERT.Init()) {
		LogInstance.WriteLog("Init Module Listener Failed");
		exit(-1);
	}

	if (UIWINDOW.Init(1, 1, 1, 1)) {
		UIWINDOW.Run();
	}
	else {
		LogInstance.WriteLog("Init UIWINDOW Failed");
	}
	MiniDump::End();
}

void ParseCommandLineArguments()
{
	int argc;
	LPWSTR* argv;
	argv = CommandLineToArgvW(::GetCommandLine(), &argc);
	for (size_t i = 0; i < argc; i++)
	{
		if (wcscmp(argv[i], L"log") == 0)
		{
			LogInstance.Enable();
		}
		if (wcscmp(argv[i], L"lang") == 0)
		{
			//ENGLISH, 0
			//KOREAN, 1 
			//CHINESE, 2 
			//JAPANESE 3
			if (i + 1 < argc)
				Language.SetLanguage(LANGUAGE(_wtoi(argv[i + 1])));
		}
	}

	::LocalFree(argv);
}