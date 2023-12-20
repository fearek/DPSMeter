#include "pch.h"
#include ".\Buff Meter\Buff.h"
#include ".\Buff Meter\Buff Meter.h"

_PLAYERBUFF::_PLAYERBUFF(uint32_t playerID, uint16_t buffid, uint8_t stack) : _playerID(playerID) {
	_buffInfo.push_back(new Buff(buffid, stack));
}

_PLAYERBUFF::~_PLAYERBUFF(){

	for (auto itr = _buffInfo.begin(); itr != _buffInfo.end(); itr++)
		delete *itr;

	_buffInfo.clear();
}

void _PLAYERBUFF::AddBuff(uint16_t buffid, uint8_t stack) {
	
	if (_isHistoryMode)
		return;

	bool find = false;

	for (auto itr = _buffInfo.begin(); itr != _buffInfo.end(); itr++) {
		if ((*itr)->GetBuffID() == buffid)
		{
			if (stack > (*itr)->GetStack())
				(*itr)->InActive();
			else if (stack == (*itr)->GetStack()) {
				(*itr)->Active();
				find = true;
			}
		}
	}

	if (!find) 
		_buffInfo.push_back(new Buff(buffid, stack));
}

void _PLAYERBUFF::EndBuff(uint16_t buffid, bool endAll) {

	if (_isHistoryMode)
		return;

	for (auto itr = _buffInfo.begin(); itr != _buffInfo.end(); itr++) {
		if ((*itr)->GetBuffID() == buffid || endAll) {
			(*itr)->InActive();
		}
	}
}

const uint32_t& _PLAYERBUFF::GetPlayerID() {
	return _playerID;
}

std::vector<Buff*>::const_iterator _PLAYERBUFF::begin() {
	return _buffInfo.begin();
}

std::vector<Buff*>::const_iterator _PLAYERBUFF::end() {
	return _buffInfo.end();
}

BuffMeter::BuffMeter() {

}

BuffMeter::~BuffMeter() {
	bool canLock = _mutex.try_lock();
	Clear();
	FreeLock();
}

void BuffMeter::Clear() {
	//for (auto itr = _playerBuffInfo.begin(); itr != _playerBuffInfo.end(); itr++)
	//	delete* itr;

	_historyMode = false;
	_playerBuffInfo.clear();
}

std::vector<PLAYERBUF*> BuffMeter::GetPlayerInfo() {
	return _playerBuffInfo;
}

void BuffMeter::SetPlayerInfo(std::vector<PLAYERBUF*> it) {
	_historyMode = true;
	_playerBuffInfo = it;
}

void BuffMeter::AddBuff(uint32_t playerID, uint16_t buffid, uint8_t stack) {

	if (_historyMode)
		return;

	for (auto itr = _playerBuffInfo.begin(); itr != _playerBuffInfo.end(); itr++) {
		if ((*itr)->GetPlayerID() == playerID) {
			(*itr)->AddBuff(buffid, stack);
			return;
		}
	}

	_playerBuffInfo.push_back(new PLAYERBUF(playerID, buffid, stack));
}

void BuffMeter::EndBuff(uint32_t playerID, uint16_t buffid, bool endAll) {

	if (_historyMode)
		return;

	for (auto itr = _playerBuffInfo.begin(); itr != _playerBuffInfo.end(); itr++) {
		if ((*itr)->GetPlayerID() == playerID || endAll) {
			(*itr)->EndBuff(buffid, endAll);
			return;
		}
	}
}

void BuffMeter::EndAllBuff() {

	EndBuff(0, 0, true);
}

std::vector<PLAYERBUF*>::const_iterator BuffMeter::find(uint32_t playerID) {

	auto itr = _playerBuffInfo.begin();

	for (; itr != _playerBuffInfo.end(); itr++) {
		if ((*itr)->GetPlayerID() == playerID)
			return itr;
	}

	return itr;
}

std::vector<PLAYERBUF*>::const_iterator BuffMeter::begin() {
	return _playerBuffInfo.begin();
}

std::vector<PLAYERBUF*>::const_iterator BuffMeter::end() {
	return _playerBuffInfo.end();
}

void BuffMeter::GetLock() {
	_mutex.lock();
}

void BuffMeter::FreeLock() {
	_mutex.unlock();
}