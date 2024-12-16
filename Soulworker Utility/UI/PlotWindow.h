#pragma once
#include "pch.h"

#define PLOTWINDOW PlotWindow::getInstance()
#include <vector>
#include <unordered_map>
#include ".\FlatBuffers\include\SW_PLOTINFO_.h"
#include ".\Damage Meter\FlatBufferUtil.h"


using namespace SoulMeterFBS::History;

struct metaInfo {
	metaInfo(uint32_t id, std::string name) {
		_id = id;
		_name = name;
	}
	uint32_t _id;
	std::string _name;
};

class PlotInfo : public MemoryPool<PlotInfo> {
private:

	std::vector<metaInfo*> _metaInfos;
	std::unordered_map<uint32_t, std::vector<double>> _dpsList;
	std::unordered_map<uint32_t, std::vector<double>> _timeList;
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

	std::unordered_map<uint32_t, std::vector<double>> _bossHpList;
	std::unordered_map<uint32_t, std::vector<double>> _bossTimeList;
	double _bhLastTime = -1;

	bool _allowed = false;

	bool _isHistoryMode = FALSE;

public:

	void AddData(uint32_t id, std::string name, double DPS, double time, bool isFirstElement);
	void AddAbData(double DPS, double time);
	void AddBdData(double DPS, double time);
	void AddJqData(BYTE stack, double time);
	void AddBossHpData(uint32_t id, uint64_t HP, double time);
	std::vector<metaInfo*> GetMetaInfo()
	{
		return _metaInfos;
	}
	std::unordered_map<uint32_t, std::vector<double>> GetTimeList()
	{
		return _timeList;
	}
	std::unordered_map<uint32_t, std::vector<double>> GetDPSList()
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
	std::unordered_map<uint32_t, std::vector<double>> GetBossHpList()
	{
		return _bossHpList;
	}
	std::unordered_map<uint32_t, std::vector<double>> GetBossTimeList()
	{
		return _bossTimeList;
	}

	void Clear()
	{
		for (auto itr = _metaInfos.begin(); itr != _metaInfos.end(); itr++)
			delete (*itr);
	}
	flatbuffers::Offset<_tPlotInfo> Serialization(flatbuffers::FlatBufferBuilder& fbb)
	{
		// _tMetaInfo
		std::vector<flatbuffers::Offset<_tMetaInfo>> vMetaInfo;
		for (auto itr = _metaInfos.begin(); itr != _metaInfos.end(); itr++)
		{
			auto fcsName = fbb.CreateString((*itr)->_name);

			_tMetaInfoBuilder tmib(fbb);

			tmib.add__id((*itr)->_id);
			tmib.add__name(fcsName);

			vMetaInfo.push_back(tmib.Finish());
		}
		auto fcvMetaInfo = fbb.CreateVector(vMetaInfo);

		// _tIntdoubleList
		std::vector<flatbuffers::Offset<_tIntDoubleList>> vIntdouble;

		// DPS
		FLATBUFFERUTIL.tIntDoubleListConverter(fbb, vIntdouble, _dpsList);
		auto fcvDpsList = fbb.CreateVector(vIntdouble);

		vIntdouble.clear();
		FLATBUFFERUTIL.tIntDoubleListConverter(fbb, vIntdouble, _timeList);
		auto fcvDpsTimeList = fbb.CreateVector(vIntdouble);

		// BossHP
		vIntdouble.clear();
		FLATBUFFERUTIL.tIntDoubleListConverter(fbb, vIntdouble, _bossHpList);
		auto fcvBossHpList = fbb.CreateVector(vIntdouble);

		vIntdouble.clear();
		FLATBUFFERUTIL.tIntDoubleListConverter(fbb, vIntdouble, _bossTimeList);
		auto fcvBossTimeList = fbb.CreateVector(vIntdouble);

		// std::vector<double>
		auto fcvABList = fbb.CreateVector(_abList);
		auto fcvABTimeList = fbb.CreateVector(_abTimeList);

		auto fcvBDList = fbb.CreateVector(_bdList);
		auto fcvBDTimeList = fbb.CreateVector(_bdTimeList);

		auto fcvJQList = fbb.CreateVector(_jqList);
		auto fcvJQTimeList = fbb.CreateVector(_jqTimeList);

		// _tPlotInfo
		_tPlotInfoBuilder tpib(fbb);

		tpib.add__meta(fcvMetaInfo);

		tpib.add__dps_list(fcvDpsList);
		tpib.add__dps_time_list(fcvDpsTimeList);

		tpib.add__ab_list(fcvABList);
		tpib.add__ab_time_list(fcvABTimeList);

		tpib.add__bd_list(fcvBDList);
		tpib.add__bd_time_list(fcvBDTimeList);

		tpib.add__jq_list(fcvJQList);
		tpib.add__jq_time_list(fcvJQTimeList);

		tpib.add__boss_hp_list(fcvBossHpList);
		tpib.add__boss_time_list(fcvBossTimeList);

		return tpib.Finish();
	}
	void UnSerialization(const _tPlotInfo* tPlotInfo)
	{
		// _tMetaInfo
		for (auto itr = tPlotInfo->_meta()->begin(); itr != tPlotInfo->_meta()->end(); itr++)
		{
			metaInfo* newMetaInfo = new metaInfo(itr->_id(), itr->_name()->c_str());
			_metaInfos.push_back(newMetaInfo);
		}

		// _tIntdoubleList
		// DPS
		for (auto itr = tPlotInfo->_dps_list()->begin(); itr != tPlotInfo->_dps_list()->end(); itr++)
		{
			FLATBUFFERUTIL.tIntdoubleListReverser(*itr, _dpsList);
		}
		for (auto itr = tPlotInfo->_dps_time_list()->begin(); itr != tPlotInfo->_dps_time_list()->end(); itr++)
		{
			FLATBUFFERUTIL.tIntdoubleListReverser(*itr, _timeList);
		}

		// BOSS HP
		for (auto itr = tPlotInfo->_boss_hp_list()->begin(); itr != tPlotInfo->_boss_hp_list()->end(); itr++)
		{
			FLATBUFFERUTIL.tIntdoubleListReverser(*itr, _bossHpList);
		}
		for (auto itr = tPlotInfo->_boss_time_list()->begin(); itr != tPlotInfo->_boss_time_list()->end(); itr++)
		{
			FLATBUFFERUTIL.tIntdoubleListReverser(*itr, _bossTimeList);
		}

		// std::vector<double>
		FLATBUFFERUTIL.fbvdoubleReverser(tPlotInfo->_ab_list(), _abList);
		FLATBUFFERUTIL.fbvdoubleReverser(tPlotInfo->_ab_time_list(), _abTimeList);

		FLATBUFFERUTIL.fbvdoubleReverser(tPlotInfo->_bd_list(), _bdList);
		FLATBUFFERUTIL.fbvdoubleReverser(tPlotInfo->_bd_time_list(), _bdTimeList);

		FLATBUFFERUTIL.fbvdoubleReverser(tPlotInfo->_jq_list(), _jqList);
		FLATBUFFERUTIL.fbvdoubleReverser(tPlotInfo->_jq_time_list(), _jqTimeList);

		_isHistoryMode = TRUE;
	}
};

class PlotWindow : public Singleton<PlotWindow> {
private:
	bool _isOpen = false;
	bool _end = false;

	PlotInfo* _pi = nullptr;

	uint32_t _selectedBossHpComboID;

	bool _historyMode = false;

	void UpdatePlotTab();
	void UpdateAbPlotTab();
	void UpdateBdPlotTab();
	void UpdateJqPlotTab();
	void UpdateBossHpPlotTab();
	void UpdateBossHpPlotCombo();
	void UpdateBossHpPlotGraph();
public:

	void AddData(uint32_t id, std::string name, double DPS, double time, bool isFirstElement);
	void AddAbData(double DPS, double time);
	void AddBdData(double DPS, double time);
	void AddJqData(BYTE stack, double time);
	void AddBossHpData(uint32_t id, uint64_t HP, double time);

	void OpenWindow();
	void Update();
	void Start();
	void End();
	void Clear();

	void SetPlotInfo(PlotInfo* p_pi);
	PlotInfo* GetPlotInfo();

	PlotWindow() : _selectedBossHpComboID(-1) {}
	~PlotWindow();

};