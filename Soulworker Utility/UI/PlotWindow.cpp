#include "pch.h"
#include "PlotWindow.h"
#include "UtillWindow.h"
#include <vector>
#include ".\Language\Region.h"
#include "Damage Meter\Damage Meter.h"
VOID PlotWindow::AddData(UINT32 id, std::string name, DOUBLE DPS, DOUBLE time, bool isFirstElement)
{
	if (isFirstElement) {
		if (_lastTime == time) {
			_allowed = false;
			return;
		}
		else {
			_allowed = true;
		}
	}
	// 첫번째가 스킵되면 나머지도 같이 스킵되어야함
	else {
		if (!_allowed) {
			return;
		}
	}
	_lastTime = time;

	auto it = metaInfos.begin();
	bool metaInfoFound = false;
	for (; it != metaInfos.end(); it++) {
		if ((*it)->_id == id) {
			metaInfoFound = true;
			break;
		}
	}

	if (!metaInfoFound) {
		metaInfos.push_back(new metaInfo(id, name));

		std::vector<double> newDPSvector;
		newDPSvector.push_back(DPS);
		dpsList.emplace(id, newDPSvector);

		std::vector<double> newTimevector;
		newTimevector.push_back(time);
		timeList.emplace(id, newTimevector);
	}
	else {
		dpsList[id].push_back(DPS);
		timeList[id].push_back(time);
	}
}
VOID PlotWindow::UpdateBossHpPlotTab()
{
	if (ImGui::BeginTabItem(Language.GetText(STR_PLOTWINDOW_BOSSHPGRAPH).c_str()))
	{
		UpdateBossHpPlotCombo();

		if (_selectedBossHpComboID != -1)
			UpdateBossHpPlotGraph();

		ImGui::EndTabItem();
	}
}
VOID PlotWindow::UpdateBossHpPlotCombo()
{
	std::unordered_map<UINT32, const CHAR*> bossInfos;

	// Get all monster data
	for (auto itr = DAMAGEMETER.begin(); itr < DAMAGEMETER.end(); itr++) {
		for (auto itr2 = (*itr)->begin(); itr2 != (*itr)->end(); itr2++) {
			if ((*itr2)->GetType() == MONSTER_NAMED || (*itr2)->GetType() == MONSTER_BOSS)
				bossInfos.emplace((*itr2)->GetID(), (*itr2)->GetName());
		}
	}

	const CHAR* comboPreview = nullptr;

	if (bossInfos.begin() != bossInfos.end()) {
		if (_selectedBossHpComboID == -1 || bossInfos.find(_selectedBossHpComboID) == bossInfos.end())
			_selectedBossHpComboID = bossInfos.begin()->first;
		comboPreview = bossInfos.at(_selectedBossHpComboID);

		if (ImGui::BeginCombo("BOSS", comboPreview, ImGuiComboFlags_HeightLarge)) {

			for (auto itr = bossInfos.begin(); itr != bossInfos.end(); itr++) {

				CHAR label[MONSTER_NAME_LEN] = { 0 };
				sprintf_s(label, MONSTER_NAME_LEN, "%s##%d", itr->second, itr->first);

				if (ImGui::Selectable(label)) {
					_selectedBossHpComboID = itr->first;
				}
			}

			ImGui::EndCombo();
		}
	}
}
VOID PlotWindow::AddBossHpData(UINT32 id, UINT64 HP, DOUBLE time)
{
	_bossHpList[id].push_back(static_cast<double>(HP / 1000000));
	_bossTimeList[id].push_back(time);
}
VOID PlotWindow::UpdateBossHpPlotGraph()
{
	auto timeList = _bossTimeList;
	auto bossHpList = _bossHpList;
	if (timeList.size() > 0) {
		size_t currentSize = timeList[_selectedBossHpComboID].size();

		// 
		DOUBLE startX = 0.0;
		if (currentSize > 45) {
			startX = timeList[_selectedBossHpComboID].at(currentSize - 45);
		}
		DOUBLE endX = timeList[_selectedBossHpComboID].at(currentSize - 1);
		//
		DOUBLE startY = 0;
		DOUBLE endY = 100;
		auto itr = bossHpList[_selectedBossHpComboID].begin();
		if (currentSize > 45) {
			itr += (bossHpList[_selectedBossHpComboID].size() - 1) - (45 - 1);
		}
		for (; itr != bossHpList[_selectedBossHpComboID].end(); itr++) {
			if (*itr > endY) {
				endY = *itr;
			}
		}
		startY = endY - 7000;
		if (startY <= 0) {
			startY = 0;
		}
		endY += 100;

		if (!_end) {
			ImPlot::SetNextPlotLimitsX(startX, endX, ImGuiCond_Always);
			ImPlot::SetNextPlotLimitsY(startY, endY, ImGuiCond_Always);
		}
	}

	if (ImPlot::BeginPlot(
		Language.GetText(STR_PLOTWINDOW_BOSSHPGRAPH).c_str(),
		Language.GetText(STR_PLOTWINDOW_TIME_SEC).c_str(),
		Language.GetText(STR_PLOTWINDOW_BOSSHPGRAPH).c_str(), ImVec2(-1, 0), ImPlotFlags_AntiAliased, ImPlotAxisFlags_None, ImPlotAxisFlags_AutoFit)) {
		ImPlot::PlotLine(Language.GetText(STR_PLOTWINDOW_BOSSHPGRAPH_UNIT).c_str(), timeList[_selectedBossHpComboID].data(), bossHpList[_selectedBossHpComboID].data(), static_cast<INT>(bossHpList[_selectedBossHpComboID].size()));
		ImPlot::EndPlot();
	}
}
VOID PlotWindow::AddAbData(DOUBLE DPS, DOUBLE time)
{
	if (_abLastTime == time) {
		return;
	}
	_abLastTime = time;

	_abList.push_back(DPS);
	_abTimeList.push_back(time);
}
VOID PlotWindow::AddBdData(DOUBLE DPS, DOUBLE time)
{
	if (_bdLastTime == time) {
		return;
	}
	_bdLastTime = time;

	_bdList.push_back(DPS);
	_bdTimeList.push_back(time);
}
VOID PlotWindow::AddJqData(BYTE stack, DOUBLE time)
{
	if (_jqLastTime == time) {
		return;
	}
	_jqLastTime = time;

	_jqList.push_back(stack);
	_jqTimeList.push_back(time);
}

VOID PlotWindow::AddAnnonation(std::string content)
{
	_annonXList.push_back(_abTimeList.back());
	_annonYList.push_back(_abList.back());
	_annonContentList.push_back(content);
}
VOID PlotWindow::AddAnnonationBD(std::string content)
{
	_annonXListBD.push_back(_bdTimeList.back());
	_annonYListBD.push_back(_bdList.back());
	_annonContentListBD.push_back(content);
}
VOID PlotWindow::OpenWindow()
{
	_isOpen = true;
}

VOID PlotWindow::Update()
{
	if (_isOpen) {

		ImGui::Begin(Language.GetText(STR_UTILWINDOW_MEOW).c_str(), &_isOpen, ImGuiWindowFlags_None);

		if (ImGui::BeginTabBar(u8"PlotWindowTab"))
		{
			UpdatePlotTab();
			UpdateAbPlotTab();
			UpdateBdPlotTab();
			UpdateJqPlotTab();
			UpdateBossHpPlotTab();
			UTILLWINDOW.Update();
		}
		ImGui::End();
	}
}

VOID PlotWindow::UpdatePlotTab()
{
	if (ImGui::BeginTabItem(Language.GetText(STR_UTILWINDOW_DPSGRAPH).c_str()))
	{
		if (timeList.size() > 0) {
			UINT32 firstId = metaInfos.front()->_id;
			UINT32 lastId = metaInfos.back()->_id;
			USHORT currentSize = timeList[firstId].size();

			// 가로
			DOUBLE startX = 0.0;
			if (currentSize > 45) {
				startX = timeList[firstId].at(currentSize - 45);
			}
			DOUBLE endX = timeList[firstId].at(currentSize - 1);
			//세로
			DOUBLE startY = 0;
			DOUBLE endY = 10000;
			if (currentSize > 45) {
				auto itr = dpsList[firstId].begin();
				itr += (dpsList[firstId].size() - 1) - (45 - 1);
				for (; itr != dpsList[firstId].end(); itr++) {
					if (*itr > endY) {
						endY = *itr;
					}
				}
			}
			else {
				auto itr = dpsList[firstId].begin();
				for (; itr != dpsList[firstId].end(); itr++) {
					if (*itr > endY) {
						endY = *itr;
					}
				}
			}
			startY = endY - 7000;
			if (startY <= 0) {
				startY = 0;
			}
			endY += 1000;

			if (!_end) {
				ImPlot::SetNextPlotLimitsX(startX, endX, ImGuiCond_Always);
				ImPlot::SetNextPlotLimitsY(startY, endY, ImGuiCond_Always);
			}
		}

		if (ImPlot::BeginPlot(Language.GetText(STR_UTILWINDOW_DPSGRAPH).c_str(), Language.GetText(STR_UTILWINDOW_DPSGRAPH_TIME_SEC).c_str(), "dps", ImVec2(-1, 0), ImPlotFlags_AntiAliased, ImPlotAxisFlags_None, ImPlotAxisFlags_AutoFit)) {
			auto it = metaInfos.begin();
			for (; it != metaInfos.end(); it++) {
				UINT32 id = (*it)->_id;
				std::string name = (*it)->_name;
				ImPlot::PlotLine(name.c_str(), timeList[id].data(), dpsList[id].data(), dpsList[id].size());
			}

			ImPlot::EndPlot();
		}
		ImGui::EndTabItem();
	}
}

VOID PlotWindow::UpdateAbPlotTab()
{
	if (ImGui::BeginTabItem(Language.GetText(STR_UTILWINDOW_ABGRAPH).c_str()))
	{
		UINT32 currentSize = _abTimeList.size();

		DOUBLE startX = 0.0;
		DOUBLE endX = 5.0;
		if (currentSize > 45) {
			startX = _abTimeList.at(currentSize - 45);
		}
		if (currentSize > 0) {
			endX = _abTimeList.back();
		}

		if (!_end) {
			ImPlot::SetNextPlotLimitsX(startX, endX, ImGuiCond_Always);
		}
		ImPlot::SetNextPlotLimitsY(0.0, 100.0, ImGuiCond_Always);
		if (ImPlot::BeginPlot(Language.GetText(STR_UTILWINDOW_ABGRAPH).c_str(), Language.GetText(STR_UTILWINDOW_ABGRAPH_TIME_SEC).c_str(), "ab", ImVec2(-1, 0), ImPlotFlags_AntiAliased, ImPlotAxisFlags_None, ImPlotAxisFlags_None)) {
			ImPlot::PlotLine(u8"YOU", _abTimeList.data(), _abList.data(), _abList.size());
			auto itr = _annonXList.begin();
			for (; itr != _annonXList.end(); itr++) {
				int currentIndex = itr - _annonXList.begin();
				ImPlot::Annotate(_annonXList.at(currentIndex),_annonYList.at(currentIndex), ImVec2(15, 15), ImVec4(0.30f, 0.30f, 0.30f, 0.84f), _annonContentList.at(currentIndex).c_str());
			}
			ImPlot::EndPlot();
		}
		ImGui::EndTabItem();
	}
}
VOID PlotWindow::UpdateBdPlotTab()
{
	if (ImGui::BeginTabItem(Language.GetText(STR_UTILWINDOW_BDGRAPH).c_str()))
	{
		UINT32 currentSize = _bdTimeList.size();

		DOUBLE startX = 0.0;
		DOUBLE endX = 5.0;
		if (currentSize > 45) {
			startX = _bdTimeList.at(currentSize - 45);
		}
		if (currentSize > 0) {
			endX = _bdTimeList.back();
		}

		if (!_end) {
			ImPlot::SetNextPlotLimitsX(startX, endX, ImGuiCond_Always);
		}
		ImPlot::SetNextPlotLimitsY(0.0, 300.0, ImGuiCond_Always);
		if (ImPlot::BeginPlot(Language.GetText(STR_UTILWINDOW_BDGRAPH).c_str(), Language.GetText(STR_UTILWINDOW_BDGRAPH_TIME_SEC).c_str(), "BD", ImVec2(-1, 0), ImPlotFlags_AntiAliased, ImPlotAxisFlags_None, ImPlotAxisFlags_None)) {
			ImPlot::PlotLine(u8"YOU", _bdTimeList.data(), _bdList.data(), _bdList.size());
			auto itr = _annonXListBD.begin();
			for (; itr != _annonXListBD.end(); itr++) {
				int currentIndex = itr - _annonXList.begin();
				ImPlot::Annotate(_annonXListBD.at(currentIndex), _annonYListBD.at(currentIndex), ImVec2(15, 15), ImVec4(0.30f, 0.30f, 0.30f, 0.84f), _annonContentListBD.at(currentIndex).c_str());
			}
			ImPlot::EndPlot();
		}
		ImGui::EndTabItem();
	}
}
VOID PlotWindow::UpdateJqPlotTab()
{
	if (ImGui::BeginTabItem(Language.GetText(STR_UTILWINDOW_JQGRAPH).c_str()))
	{
		UINT32 currentSize = _jqTimeList.size();
		DOUBLE startX = 0.0;
		DOUBLE endX = 5.0;
		if (currentSize > 45) {
			startX = _jqTimeList.at(currentSize - 45);
		}
		if (currentSize > 0) {
			endX = _jqTimeList.back();
		}
		if (!_end) {
			ImPlot::SetNextPlotLimitsX(startX, endX, ImGuiCond_Always);
		}
		ImPlot::SetNextPlotLimitsY(0, 4, ImGuiCond_Always);
		if (ImPlot::BeginPlot(Language.GetText(STR_UTILWINDOW_JQGRAPH).c_str(), Language.GetText(STR_UTILWINDOW_JQGRAOH_TIME_SEC).c_str(), "stack", ImVec2(-1, 0), ImPlotFlags_AntiAliased, ImPlotAxisFlags_None, ImPlotAxisFlags_None)) {
			ImPlot::PlotLine(u8"YOU", _jqTimeList.data(), _jqList.data(), _jqList.size());
			ImPlot::EndPlot();
		}
		ImGui::EndTabItem();
	}
}



VOID PlotWindow::End()
{
	_end = true;
}

VOID PlotWindow::Clear()
{
	_end = false;
	metaInfos.clear();
	dpsList.clear();
	timeList.clear();

	_abList.clear();
	_abTimeList.clear();
	_bdList.clear();
	_bdTimeList.clear();
	_jqList.clear();
	_jqTimeList.clear();

	_lastTime = -1.0;
	_abLastTime = -1.0;
	_bdLastTime = -1.0;
	_jqLastTime = -1.0;
	// TODO : new로 생성한건 delete인가 해야됨
}

PlotWindow::PlotWindow() : _selectedBossHpComboID(-1)
{
}

PlotWindow::~PlotWindow()
{
}
