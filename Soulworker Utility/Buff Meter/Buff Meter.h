#pragma once
#include "pch.h"
#include ".\Buff Meter\Buff.h"
#include ".\FlatBuffers\include\SW_HISTORY_.h"

using namespace SoulMeterFBS::History;

#define BUFFMETER BuffMeter::getInstance()

typedef struct _PLAYERBUFF {
private:
	uint32_t _playerID;
	std::vector<Buff*> _buffInfo;
	bool _isHistoryMode = false;

protected:
	_PLAYERBUFF(const _PLAYERBUFF& other) {}

public:
	_PLAYERBUFF() {}
	_PLAYERBUFF(uint32_t playerID, uint16_t buffid, uint8_t stack);
	~_PLAYERBUFF();

	void AddBuff(uint16_t buffid, uint8_t stack);
	void EndBuff(uint16_t buffid, bool endAll = false);

	const uint32_t& GetPlayerID();

	std::vector<Buff*>::const_iterator begin();
	std::vector<Buff*>::const_iterator end();

	void Serialization(flatbuffers::FlatBufferBuilder& fbb, std::vector<flatbuffers::Offset<_tBuff>>& vBuff)
	{
		// _tBuffInfo
		std::vector<flatbuffers::Offset<_tBuffInfo>> vBuffInfo;
		for (auto itr = begin(); itr != end(); itr++)
			(*itr)->Serialization(fbb, vBuffInfo);
		auto fcvBuffInfo = fbb.CreateVector(vBuffInfo);

		// _tBuff
		_tBuffBuilder tbb(fbb);
		tbb.add__id(_playerID);
		tbb.add__buff_info(fcvBuffInfo);

		vBuff.push_back(tbb.Finish());
	}
	void UnSerialization(const _tBuff* tBuff)
	{
		// _tBuffInfo
		for (auto itr = tBuff->_buff_info()->begin(); itr != tBuff->_buff_info()->end(); itr++)
		{
			Buff* newBuff = new Buff;
			newBuff->UnSerialization(*itr);

			_buffInfo.push_back(newBuff);
		}

		// _tBuff
		_playerID = tBuff->_id();

		_isHistoryMode = true;
	}
}PLAYERBUF;

class BuffMeter : public Singleton<BuffMeter> {
private:
	std::vector<PLAYERBUF*> _playerBuffInfo;

	bool _historyMode = false;

	std::mutex _mutex;

public:
	BuffMeter();
	~BuffMeter();

	std::vector<PLAYERBUF*> GetPlayerInfo();
	void SetPlayerInfo(std::vector<PLAYERBUF*> it);
	void Clear();

	void AddBuff(uint32_t playerID, uint16_t buffid, uint8_t stack);
	void EndBuff(uint32_t playerID, uint16_t buffid, bool endAll = false);
	void EndAllBuff();

	std::vector<PLAYERBUF*>::const_iterator find(uint32_t playerID);
	std::vector<PLAYERBUF*>::const_iterator begin();
	std::vector<PLAYERBUF*>::const_iterator end();

	void GetLock();
	void FreeLock();
};