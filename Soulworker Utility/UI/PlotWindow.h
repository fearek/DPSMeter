#pragma once
#include "pch.h"

#define PLOTWINDOW PlotWindow::getInstance()
#include <vector>
#include <unordered_map>

struct metaInfo {
	metaInfo(UINT32 id, std::wstring name) {
		_id = id;
		_name = name;
	}
	UINT32 _id;
	std::wstring _name;
};

struct damageInfo {
	damageInfo(double dps, double time) {
		_dps = dps;
		_time = time;
	}
	double _dps;
	double _time;
};

class PlotWindow : public Singleton<PlotWindow> {
private:
	std::vector<metaInfo*> metaInfos;
	std::unordered_map<UINT32, std::vector<double>> dpsList;
	std::unordered_map<UINT32, std::vector<double>> timeList;
	bool _isOpen = false;
	bool _allowed = false;
	double _lastTime = -1;

	std::vector<double> _abList;
	std::vector<double> _abTimeList;
	double _abLastTime = -1;

	std::vector<double> _bdList;
	std::vector<double> _bdTimeList;
	double _bdLastTime = -1;

	std::vector<double> _jqList;
	std::vector<double> _jqTimeList;
	double _jqLastTime = -1;

	std::vector<double> _annonXList;
	std::vector<double> _annonYList;
	std::vector<std::string> _annonContentList;

	std::vector<double> _annonXListBD;
	std::vector<double> _annonYListBD;
	std::vector<std::string> _annonContentListBD;

	bool _end = false;

	VOID UpdatePlotTab();
	VOID UpdateAbPlotTab();
	VOID UpdateJqPlotTab();
	VOID UpdateBdPlotTab();
public:
	VOID AddData(UINT32 id, std::wstring name, DOUBLE DPS, DOUBLE time, bool isFirstElement);
	VOID AddAbData(DOUBLE DPS, DOUBLE time);
	VOID AddBdData(DOUBLE DPS, DOUBLE time);
	VOID AddJqData(BYTE stack, DOUBLE time);
	VOID AddAnnonation(std::string content); //armor break
	VOID AddAnnonationBD(std::string content);
	VOID OpenWindow();
	VOID Update();
	VOID End();
	VOID Clear();

	PlotWindow();
	~PlotWindow();

};