#pragma once
#include "pch.h"
#include ".\FlatBuffers\include\SW_HISTORY_.h"

using namespace SoulMeterFBS::History;

#define BUFF_NAME_LEN 64
#define BUFF_DESC_LEN 256

class Buff : public MemoryPool<Buff> {
private:
	uint16_t _buffID;
	uint8_t _stack;
	char _name[BUFF_NAME_LEN];
	char _desc[BUFF_DESC_LEN];

	timePoint _timePoint;
	float _time;

	bool _isActive;

	bool _isHistoryMode = false;

protected:
	Buff(const Buff& other) {}

public:
	Buff() {}
	Buff(uint16_t buffID, uint8_t stack);
	
	void Update();

	void Active();
	void InActive();

	const uint16_t& GetBuffID();
	const uint8_t& GetStack();
	const float& GetTime();
	const char* GetName();
	const char* GetDesc();

	void SetNameFromDB();

	void Serialization(flatbuffers::FlatBufferBuilder& fbb, std::vector<flatbuffers::Offset<_tBuffInfo>>& vBuffInfo)
	{
		_tBuffInfoBuilder tbib(fbb);

		tbib.add__buff_id(GetBuffID());
		tbib.add__stack(GetStack());
		tbib.add__time(GetTime());

		vBuffInfo.push_back(tbib.Finish());
	}

	void UnSerialization(const _tBuffInfo* tBuffInfo)
	{
		_buffID = tBuffInfo->_buff_id();
		_stack = tBuffInfo->_stack();
		_time = tBuffInfo->_time();

		SetNameFromDB();

		_isHistoryMode = true;
	}
};