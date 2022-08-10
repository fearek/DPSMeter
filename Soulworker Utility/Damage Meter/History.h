#pragma once
#include ".\Damage Meter\SWDamagePlayer.h"

#define HISTORY SWDamageMeterHistory::getInstance()
#define HISTORY_SIZE 10

typedef struct _HISTORYINFO {
public:
	std::vector<SWDamagePlayer*> _history;
	UINT32 _myID;
	UINT32 _worldID;
	UINT32 _ping;
	SYSTEMTIME _saveTime;
	FLOAT _time;

	VOID Setup(std::vector<SWDamagePlayer*>& history, UINT32 worldID, FLOAT time, UINT32 ping,UINT32 myID);
	VOID Clear();
}HISTORY_INFO;

class SWDamageMeterHistory : public Singleton<SWDamageMeterHistory> {
private:
	HISTORY_INFO _historys[HISTORY_SIZE];
	UINT _curIndex;
	
	VOID ClearHistory(INT index);

public:
	SWDamageMeterHistory() : _curIndex(0) {}
	~SWDamageMeterHistory();

	VOID push_back(std::vector<SWDamagePlayer*>& playerInfo);
	SIZE_T size();
	const HISTORY_INFO& operator[](INT index);
};