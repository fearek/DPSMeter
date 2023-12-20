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

	char _searchData[MAX_PATH] = { 0 };
	char _searchData2[MAX_PATH] = { 0 };
	int32_t _currentIndex = 0;

	Combat* _ci = nullptr;
	std::vector<std::pair<uint32_t, std::string>> _combatTmp;
	std::mutex _mutex;

	std::vector<std::pair<HISTORY_INFO*, std::string>> _historyTmp;

	void handleDialogInfo();
	void HistoryWindow();

	void CombatWindow();
	void ForceUpdateCombatTemp(Combat* pCombat);
public:

	void OpenWindow();
	void Update();

	UtillWindow();
	~UtillWindow();

	void ClearCombatTemp();
};