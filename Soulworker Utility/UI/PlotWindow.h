#pragma once
#include "pch.h"

#define PLOTWINDOW PlotWindow::getInstance()
#include <vector>
#include <unordered_map>

struct metaInfo {
	metaInfo(UINT32 id, std::string name) {
		_id = id;
		_name = name;
	}
	UINT32 _id;
	std::string _name;
};

struct damageInfo {
	damageInfo(double dps, double time) {
		_dps = dps;
		_time = time;
	}
	double _dps;
	double _time;
};
class PlotInfo : public MemoryPool<PlotInfo> {
private:
	std::vector<metaInfo*> _metaInfos;
	std::unordered_map<UINT32, std::vector<double>> _dpsList;
	std::unordered_map<UINT32, std::vector<double>> _timeList;
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

	std::unordered_map<UINT32, std::vector<double>> _bossHpList;
	std::unordered_map<UINT32, std::vector<double>> _bossTimeList;
	double _bhLastTime = -1;

	bool _allowed = false;

	BOOL _isHistoryMode = FALSE;

public:

	VOID AddData(UINT32 id, std::string name, DOUBLE DPS, DOUBLE time, bool isFirstElement);
	VOID AddAbData(DOUBLE DPS, DOUBLE time);
	VOID AddBdData(DOUBLE DPS, DOUBLE time);
	VOID AddJqData(BYTE stack, DOUBLE time);
	VOID AddBossHpData(UINT32 id, UINT64 HP, DOUBLE time);
	std::vector<metaInfo*> GetMetaInfo()
	{
		return _metaInfos;
	}
	std::unordered_map<UINT32, std::vector<double>> GetTimeList()
	{
		return _timeList;
	}
	std::unordered_map<UINT32, std::vector<double>> GetDPSList()
	{
		return _dpsList;
	}
	std::vector<double> GetABList()
	{
		return _abList;
	}
	std::vector<double> GetABTimeList()
	{
		return _abTimeList;
	}
	std::vector<double> GetBDList()
	{
		return _bdList;
	}
	std::vector<double> GetBDTimeList()
	{
		return _bdTimeList;
	}
	std::vector<double> GetJQList()
	{
		return _jqList;
	}
	std::vector<double> GetJQTimeList()
	{
		return _jqTimeList;
	}
	std::unordered_map<UINT32, std::vector<double>> GetBossHpList()
	{
		return _bossHpList;
	}
	std::unordered_map<UINT32, std::vector<double>> GetBossTimeList()
	{
		return _bossTimeList;
	}

	VOID Clear()
	{
		for (auto itr = _metaInfos.begin(); itr != _metaInfos.end(); itr++)
			delete (*itr);
	}

};
class PlotWindow : public Singleton<PlotWindow> {
private:
	std::vector<metaInfo*> metaInfos;
	std::unordered_map<UINT32, std::vector<double>> dpsList;
	std::unordered_map<UINT32, std::vector<double>> timeList;
	PlotInfo* _pi = nullptr;
	BOOL _historyMode = false;
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

	std::unordered_map<UINT32, std::vector<double>> _bossHpList;
	std::unordered_map<UINT32, std::vector<double>> _bossTimeList;
	UINT32 _selectedBossHpComboID;

	bool _end = false;

	VOID UpdatePlotTab();
	VOID UpdateAbPlotTab();
	VOID UpdateJqPlotTab();
	VOID UpdateBdPlotTab();
	VOID UpdateBossHpPlotTab();
	VOID UpdateBossHpPlotGraph();
	VOID UpdateBossHpPlotCombo();
public:
	VOID AddData(UINT32 id, std::string name, DOUBLE DPS, DOUBLE time, bool isFirstElement);
	VOID AddAbData(DOUBLE DPS, DOUBLE time);
	VOID AddBdData(DOUBLE DPS, DOUBLE time);
	VOID AddJqData(BYTE stack, DOUBLE time);
	VOID AddAnnonation(std::string content); //armor break
	VOID AddAnnonationBD(std::string content);
	VOID AddBossHpData(UINT32 id, UINT64 HP, DOUBLE time);
	VOID OpenWindow();
	VOID Update();
	VOID Start();
	VOID End();
	VOID Clear();
	PlotWindow();
	~PlotWindow();

};