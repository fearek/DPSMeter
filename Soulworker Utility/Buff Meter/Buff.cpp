#include "pch.h"
#include ".\Buff Meter\Buff.h"
#include ".\Damage Meter\MySQLite.h"

Buff::Buff(uint16_t buffID, uint8_t stack) : _buffID(buffID), _stack(stack) {
	_timePoint = std::chrono::system_clock::now();
	_time = 0;

	SetNameFromDB();
}

void Buff::SetNameFromDB()
{
	ZeroMemory(&_desc, BUFF_DESC_LEN);
	SWDB.GetBuffName(_buffID, _name, BUFF_NAME_LEN, _desc, BUFF_DESC_LEN);

	char stackName[8] = { 0 };
	sprintf_s(stackName, 8, "(%d)", _stack);
	strcat_s(_name, BUFF_NAME_LEN, stackName);
}

void Buff::Update() {
	if (_isHistoryMode)
		return;

	if (_isActive) {
		std::chrono::duration<float> time;
		time = std::chrono::system_clock::now() - _timePoint;
		_time += time.count();
		_timePoint = std::chrono::system_clock::now();
	}
}

void Buff::Active() {
	if (_isHistoryMode)
		return;

	_timePoint = std::chrono::system_clock::now();
	_isActive = true;
}

void Buff::InActive() {
	if (_isHistoryMode)
		return;

	if (_isActive) {
		std::chrono::duration<float> time;
		time = std::chrono::system_clock::now() - _timePoint;
		_time += time.count();
		_timePoint = std::chrono::system_clock::now();
	}

	_isActive = false;
}

const uint16_t& Buff::GetBuffID() {
	return _buffID;
}

const uint8_t& Buff::GetStack() {
	return _stack;
}

const float& Buff::GetTime() {

	Update();

	return _time;
}

const char* Buff::GetName() {
	return _name;
}

const char* Buff::GetDesc() {
	return _desc;
}