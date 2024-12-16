#pragma once
#include ".\Damage Meter\SWDamagePlayer.h"
#include ".\Buff Meter\Buff Meter.h"
#include ".\UI\PlotWindow.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Third Party\FlatBuffers\include\SW_HISTORY_.h"
#include ".\Combat Meter\Combat.h"

using namespace SoulMeterFBS::History;

#define HISTORY SWDamageMeterHistory::getInstance()
#define HISTORY_SIZE 50

struct HISTORY_DATA
{
	std::vector<SWDamagePlayer*> _playerHistory;
	std::vector<SW_DB2_STRUCT*> _dbHistory;
	std::vector<PLAYERBUF*> _buffHistory;
	PlotInfo* _plotHistory = nullptr;
	std::unordered_map<uint32_t, SWDamageMeter::SW_PLAYER_METADATA*> _playerMetadata;
	std::string _extInfo;
	CombatInterface* _combatIF = nullptr;
};

typedef struct _HISTORYINFO {
public:
	uint32_t _worldID;
	SYSTEMTIME* _saveTime;
	uint64_t _time;
	HISTORY_DATA* _historyData;
	uint32_t _myID;
	uint32_t _realClearTime;
	bool _isSaveData = FALSE;

	void Setup(HISTORY_DATA* historyData, uint32_t worldID, uint64_t time, uint32_t myID, bool isSaveData = FALSE, SYSTEMTIME* saveTime = nullptr, uint32_t realClearTime = 0);
	void Clear();

	flatbuffers::Offset<_tHistory> Serialization(flatbuffers::FlatBufferBuilder& fbb, HISTORY_DATA* historyData);
}HISTORY_INFO;

class SWDamageMeterHistory : public Singleton<SWDamageMeterHistory> {
private:
	std::vector<LPVOID> _historys;
	int _curIndex = 0;
	
	std::mutex _mutex;

	bool _stopAddHistory = FALSE;

public:
	SWDamageMeterHistory() : _curIndex(0) {}
	~SWDamageMeterHistory();

	void push_back(HISTORY_INFO* pHi);
	void ClearHistory(HISTORY_INFO* pHI = nullptr, bool deleteFirst = TRUE);
	void ClearAll();
	void ClearVector();

	void UnSerialization(const _tHistory* pHistory);

	int GetCurrentIndex()
	{
		return _curIndex;
	}

	void GetLock()
	{
		_mutex.lock();
	}

	void FreeLock()
	{
		_mutex.unlock();
	}

	auto begin()
	{
		return _historys.begin();
	}

	auto end()
	{
		return _historys.end();
	}

	auto rbegin()
	{
		return _historys.rbegin();
	}

	auto rend()
	{
		return _historys.rend();
	}

	const size_t size()
	{
		return _historys.size();
	}

	bool isStop()
	{
		return _stopAddHistory;
	}
};