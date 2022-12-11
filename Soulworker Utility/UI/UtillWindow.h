#pragma once
#include "pch.h"
#include ".\FlatBuffers\include\SW_HISTORY_.h"
#include ".\Damage Meter\History.h"
#include ".\Damage Meter\MySQLite.h"
#include ".\Damage Meter\SaveData.h"
#include ".\UI\UiWindow.h"
#include ".\Combat Meter\CombatMeter.h"
#include ".\Combat Meter\Combat.h"

using namespace SoulMeterFBS::History;

#define UTILLWINDOW UtillWindow::getInstance()

class UtillWindow : public Singleton<UtillWindow> {
private:
	bool _isOpen = false;

	ImFileDialogInfo _fileDialogInfo;
	bool _fileDialogOpen = false;

	CHAR _searchData[MAX_PATH] = { 0 };
	CHAR _searchData2[MAX_PATH] = { 0 };
	INT32 _currentIndex = 0;

	Combat* _ci = nullptr;
	std::vector<std::pair<UINT32, std::string>> _combatTmp;
	std::mutex _mutex;

	std::vector<std::pair<HISTORY_INFO*, std::string>> _historyTmp;

	VOID handleDialogInfo();
	VOID HistoryWindow();

	VOID CombatWindow();
	VOID ForceUpdateCombatTemp(Combat* pCombat);
public:

	VOID OpenWindow();
	VOID Update();

	UtillWindow();
	~UtillWindow();

	VOID ClearCombatTemp();
};