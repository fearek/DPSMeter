#pragma once
#include "pch.h"
#include ".\Combat Meter\Combat.h"
#include ".\FlatBuffers\include\SW_HISTORY_.h"
#include ".\Soulworker Packet\PacketInfo.h"

using namespace SoulMeterFBS::History;

#define COMBATMETER CombatMeter::getInstance()

class CombatMeter : public Singleton<CombatMeter> {
private:
	bool _historyMode = false;
	bool _isEnd = false;

	std::mutex _mutex;

	CombatInterface* _ci = nullptr;

public:
	CombatMeter() {}
	~CombatMeter()
	{
		bool a = _mutex.try_lock();
		_mutex.unlock();
	}

	auto Get()
	{
		return _ci;
	}
	void Set(CombatInterface* ci)
	{
		GetLock();
		{
			if (!_historyMode && _ci != nullptr)
			{
				_ci->Clear();
				delete _ci;
			}

			_ci = ci;
			_historyMode = true;
			FreeLock();
		}
	}
	void Clear(bool realClear = FALSE)
	{
		GetLock();
		{
			if (!_historyMode && realClear && _ci != nullptr)
			{
				_ci->Clear();
				delete _ci;
			}
			_ci = nullptr;
			_historyMode = false;
			_isEnd = false;
			FreeLock();
		}
	}
	void End()
	{
		GetLock();
		{
			_isEnd = TRUE;
			FreeLock();
		}
	}

	void Insert(uint32_t id, CombatType type, CombatLog* cl);

	std::string ConvertCombatLogVal(CombatLog* pCombatLog, CombatType type);
	std::string GetName(Combat* pCombat);
	CombatLogType ConvertDamageTypeForGiveDamage(SWPACKETDAMAGE_DAMAGETYPE damageType);
	CombatLogType ConvertDamageTypeForTakeDamage(SWPACKETDAMAGE_DAMAGETYPE damageType);

	void GetLock()
	{
		_mutex.lock();
	}
	void FreeLock()
	{
		_mutex.unlock();
	}
};