#pragma once
#include ".\Buff Meter\Buff.h"

#define BUFFMETER BuffMeter::getInstance()

typedef struct _PLAYERBUFF {
private:
	UINT32 _playerID;
	std::vector<Buff*> _buffInfo;

protected:
	_PLAYERBUFF() {}
	_PLAYERBUFF(const _PLAYERBUFF& other) {}

public:
	_PLAYERBUFF(UINT32 playerID, USHORT buffid, BYTE stack);
	~_PLAYERBUFF();

	VOID AddBuff(USHORT buffid, BYTE stack);
	VOID EndBuff(USHORT buffid);

	const UINT32& GetPlayerID();

	std::vector<Buff*>::const_iterator begin();
	std::vector<Buff*>::const_iterator end();

}PLAYERBUF;

class BuffMeter : public Singleton<BuffMeter> {
private:
	std::vector<PLAYERBUF*> _playerBuffInfo;

	std::mutex _mutex;

public:
	BuffMeter();
	~BuffMeter();

	VOID AddBuff(UINT32 playerID, USHORT buffid, BYTE stack);
	VOID EndBuff(UINT32 playerID, USHORT buffid);

	std::vector<PLAYERBUF*>::const_iterator find(UINT32 playerID);
	std::vector<PLAYERBUF*>::const_iterator begin();
	std::vector<PLAYERBUF*>::const_iterator end();

	VOID GetLock();
	VOID FreeLock();
};