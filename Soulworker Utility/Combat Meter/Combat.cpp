#include "pch.h"
#include ".\Combat Meter\Combat.h"

void Combat::Insert(CombatLog* cl)
{
	if (_isHistory)
		return;

	SYSTEMTIME* time = new SYSTEMTIME;
	GetLocalTime(time);

	cl->_time = time;

	_log.push_back(std::pair(GetCurrentTimeStamp(), cl));
}

void Combat::Clear()
{
	for (auto itr = _log.begin(); itr != _log.end(); itr++)
	{
		delete itr->second->_time;
		delete itr->second;
	}

	_log.clear();
}

void CombatInterface::Insert(uint32_t id, CombatType type, CombatLog* cl)
{
	if (_isHistory)
		return;

	Combat* pCombat = nullptr;

	auto find = _combat.find(id);
	if (find == _combat.end())
	{
		pCombat = new Combat(id, type);
		_combat[id] = pCombat;
	}
	else {
		pCombat = find->second;
	}

	pCombat->Insert(cl);
}

void CombatInterface::Clear()
{
	for (auto itr = _combat.begin(); itr != _combat.end(); itr++)
	{
		itr->second->Clear();
		delete itr->second;
	}
	_combat.clear();
}