#pragma once
#include ".\Damage Meter\SWDamageMonster.h"
#include ".\Soulworker Packet\PacketInfo.h"
#include ".\Damage Meter\MonsterList.h"
#include <unordered_set>
#include <map>
#include ".\Third Party\FlatBuffers\include\SW_HISTORY_.h"
using namespace SoulMeterFBS::History;

#define DEBUG_DAMAGE_PLAYER 0

struct SkillCount {
	uint16_t _count;
	uint16_t _in_full_ab_count;
};

class SWDamagePlayer : public MemoryPool<SWDamagePlayer, 30> {
private:
	uint32_t _id;
	uint64_t _damage;
	uint64_t _soulstoneDamage;
	uint16_t _hitCount;
	uint16_t _critHitCount;
	uint16_t _maxCombo;
	uint16_t _hitCountForCritRate;
	uint16_t _critHitCountForCritRate;
	uint16_t _missCount;
	uint16_t _soulstoneCount;
	uint64_t _damageForSoulstone;
	uint64_t _soulstoneDamageForSoulstone;
	uint16_t _hitCountForArmorBreak;
	float _armorBreak;
	float _sg;
	float _stamina;
	float _sv;
	float _attackSpeed;
	float _partialDamage;
	uint16_t _getHitAll;
	uint16_t _getHit;
	uint16_t _getHitBS;
	uint16_t _getHitMissed;
	uint16_t _getHitMissedReal;
	float _enlightenSum;
	uint16_t _gigaEnlightenProc;
	uint16_t _teraEnlightenProc;
	uint16_t _skillCounts = 0;
	uint16_t _dodgeCounts = 0;
	uint16_t _deathCounts = 0;

	double _historyAvgAB = 0.0;
	double _historyAvgBD = 0.0;

	double _historygear90 = 0.0;
	double _historygear50 = 0.0;
	double _historyacc01 = 0.0;
	double _historyacc02 = 0.0;

	double _historyLosedHP = 0.0;
	uint8_t _JqStack = 0;

	double _historyABTime = 0;

	double _historyAggroTime = 0;

	double _historyASTime = 0;
	double _historyAvgAS = 0.0;

	std::vector<SWDamageMonster*> _monsterInfo;
	void InsertMonsterInfo(uint32_t monsterID, uint64_t damage, uint64_t critDamage, uint16_t hitCount, uint16_t critHitCount, uint32_t skillID);
	void Sort();

protected:
	

public:
	SWDamagePlayer() : _id(0), _damage(0), _soulstoneDamage(0), _hitCount(0), _critHitCount(0), _maxCombo(0),
		_hitCountForCritRate(0), _critHitCountForCritRate(0), _soulstoneCount(0), _hitCountForArmorBreak(0),
		_armorBreak(0), _sg(0), _stamina(0), _sv(0), _attackSpeed(0), _partialDamage(0.0f) { }
	SWDamagePlayer(uint32_t id, uint64_t damage, uint64_t soulstoneDamage, SWPACKETDAMAGE_DAMAGETYPE damageType, uint16_t maxCombo, uint32_t monsterID, uint32_t skillID);
	SWDamagePlayer(uint32_t id);
	~SWDamagePlayer();

	std::map<uint32_t, SkillCount*> skillCounts;

	static bool SortFunction(SWDamagePlayer* playerA, SWDamagePlayer* playerB);

	uint32_t GetID();
	uint64_t GetDamage();
	uint64_t GetSoulstoneDamage();
	uint16_t GetHitCount();
	uint16_t GetCritHitCount();
	uint16_t GetMaxCombo();
	uint64_t GetMonsterTotalDamage();
	uint16_t GetHitCountForCritRate();
	uint16_t GetCritHitCountForCritRate();
	uint16_t GetMissCount();
	uint16_t GetSoulstoneCount();
	uint64_t GetDamageForSoulstone();
	uint64_t GetSoulStoneDamageForSoulstone();
	uint16_t GetGetHitAll();
	uint16_t GetGetHit();
	uint16_t GetGetHitBS();
	uint16_t GetGetHitMissed();
	uint16_t GetGetHitMissedReal();
	float GetEnlightenSum();
	uint16_t GetGigaEnlighten();
	uint16_t GetTeraEnlighten();
	uint16_t GetSkillUsed();
	uint16_t GetDodgeUsed();
	uint16_t GetDeathCount();

	double GetHistoryABTime();
	void SetHistoryABTime(double historyABTime);

	void SetHistoryAvgAB(double historyAvgAB);
	double GetHistoryAvgAB();

	void SetHistoryAvgBD(double historyAvgBD);
	double GetHistoryAvgBD();

	void SetHistoryAggroTime(double t);
	double GetHistoryAggroTime();

	double GetHistoryASTime();
	void SetHistoryASTime(double d);

	void SetHistoryAvgAS(double d);
	double GetHistoryAvgAS();

	void setHistoryBS(int type, double value);
	double GetHistoryBS(int type);

	void setHistoryLosedHP(double losedHP);
	double GetHistoryLosedHP();

	void SetJqStack(uint8_t stack);
	uint8_t GetJqStack();

	void AddGetDamage(uint64_t totalDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, uint32_t monsterID, uint32_t skillID);
	void AddEnlighten(float value);
	void AddSkillUsed(uint32_t skillId);
	void AddDodgeUsed();
	void AddDeathCount();

	std::vector<SWDamageMonster*>::const_iterator GetMonsterInfo(unsigned int id);
	std::vector<SWDamageMonster*>::const_iterator begin();
	std::vector<SWDamageMonster*>::const_iterator end();
	const SIZE_T size();

	void AddDamage(uint64_t totalDMG, uint64_t soulstoneDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, uint16_t maxCombo, uint32_t monsterID, uint32_t skillID);

	void Serialization(flatbuffers::FlatBufferBuilder& fbb, std::vector<flatbuffers::Offset<_tDamagePlayer>>& vDamagePlayer)
	{
		// _tDamageMonster
		std::vector<flatbuffers::Offset<_tDamageMonster>> vDamageMonster;
		for (auto itr = _monsterInfo.begin(); itr != _monsterInfo.end(); itr++)
			(*itr)->Serialization(fbb, vDamageMonster);

		// _tSkillCount
		std::vector<flatbuffers::Offset<_tSkillCount>> vSkillCount;
		for (auto itr = skillCounts.begin(); itr != skillCounts.end(); itr++) {
			_tSkillCountBuilder tscb(fbb);

			tscb.add__id(itr->first);
			tscb.add__count(itr->second->_count);
			tscb.add__in_full_ab_count(itr->second->_in_full_ab_count);

			vSkillCount.push_back(tscb.Finish());
		}

		auto fcvDamageMonster = fbb.CreateVector(vDamageMonster);
		auto fcvSkillCount = fbb.CreateVector(vSkillCount);

		// _tDamagePlayer
		_tDamagePlayerBuilder tdpb(fbb);

		tdpb.add__id(_id);
		tdpb.add__damage(_damage);
		tdpb.add__soulstonedamage(_soulstoneDamage);
		tdpb.add__hitcount(_hitCount);
		tdpb.add__crithitcount(_critHitCount);

		tdpb.add__maxcombo(_maxCombo);
		tdpb.add__hitcountforcritrate(_hitCountForCritRate);
		tdpb.add__crithitcountforcritrate(_critHitCountForCritRate);
		tdpb.add__misscount(_missCount);
		tdpb.add__soulstonecount(_soulstoneCount);

		tdpb.add__damageforsoulstone(_damageForSoulstone);
		tdpb.add__soulstonedamageforsoulstone(_soulstoneDamageForSoulstone);
		tdpb.add__hitcountforarmorbreak(_hitCountForArmorBreak);
		tdpb.add__armorbreak(_armorBreak);
		tdpb.add__sg(_sg);

		tdpb.add__stamina(_stamina);
		tdpb.add__sv(_sv);
		tdpb.add__attackspeed(_attackSpeed);
		tdpb.add__partialdamage(_partialDamage);
		tdpb.add__gethitall(_getHitAll);

		tdpb.add__gethit(_getHit);
		tdpb.add__gethitbs(_getHitBS);
		tdpb.add__gethitmissed(_getHitMissed);
		tdpb.add__gethitmissedreal(_getHitMissedReal);
		tdpb.add__enlightensum(_enlightenSum);

		tdpb.add__gigaenlightenproc(_gigaEnlightenProc);
		tdpb.add__teraenlightenproc(_teraEnlightenProc);
		tdpb.add__skillcounts(_skillCounts);
		tdpb.add__dodgecounts(_dodgeCounts);
		tdpb.add__deathcounts(_deathCounts);

		tdpb.add__historyavgab(_historyAvgAB);
		tdpb.add__historyavgbd(_historyAvgBD);
		tdpb.add__historygear90(_historygear90);
		tdpb.add__historygear50(_historygear50);
		tdpb.add__historyacc01(_historyacc01);

		tdpb.add__historyacc02(_historyacc02);
		tdpb.add__historylosedhp(_historyLosedHP);
		tdpb.add__jqstack(_JqStack);
		tdpb.add__historyabtime(_historyABTime);

		tdpb.add__monsterinfo(fcvDamageMonster);
		tdpb.add__skillcount(fcvSkillCount);

		tdpb.add__historyaggrotime(_historyAggroTime);

		tdpb.add__historyavgas(_historyAvgAS);
		tdpb.add__historyastime(_historyASTime);
		
		vDamagePlayer.push_back(tdpb.Finish());
	}
	void UnSerialization(const _tDamagePlayer* tDamagePlayer)
	{
		// _tDamageMonster
		for (auto itr = tDamagePlayer->_monsterinfo()->begin(); itr != tDamagePlayer->_monsterinfo()->end(); itr++)
		{
			SWDamageMonster* newDamageMonster = new SWDamageMonster;
			newDamageMonster->UnSerialization(*itr);

			_monsterInfo.push_back(newDamageMonster);
		}

		// _tSkillCount
		for (auto itr = tDamagePlayer->_skillcount()->begin(); itr != tDamagePlayer->_skillcount()->end(); itr++)
		{
			SkillCount* newSkillCount = new SkillCount;
			newSkillCount->_count = itr->_count();
			newSkillCount->_in_full_ab_count = itr->_in_full_ab_count();

			skillCounts[itr->_id()] = newSkillCount;
		}

		_id = tDamagePlayer->_id();
		_damage = tDamagePlayer->_damage();
		_soulstoneDamage = tDamagePlayer->_soulstonedamage();
		_hitCount = tDamagePlayer->_hitcount();
		_critHitCount = tDamagePlayer->_crithitcount();

		_maxCombo = tDamagePlayer->_maxcombo();
		_hitCountForCritRate = tDamagePlayer->_hitcountforcritrate();
		_critHitCountForCritRate = tDamagePlayer->_crithitcountforcritrate();
		_missCount = tDamagePlayer->_misscount();
		_soulstoneCount = tDamagePlayer->_soulstonecount();

		_damageForSoulstone = tDamagePlayer->_damageforsoulstone();
		_soulstoneDamageForSoulstone = tDamagePlayer->_soulstonedamageforsoulstone();
		_hitCountForArmorBreak = tDamagePlayer->_hitcountforarmorbreak();
		_armorBreak = tDamagePlayer->_armorbreak();
		_sg = tDamagePlayer->_sg();

		_stamina = tDamagePlayer->_stamina();
		_sv = tDamagePlayer->_sv();
		_attackSpeed = tDamagePlayer->_attackspeed();
		_partialDamage = tDamagePlayer->_partialdamage();
		_getHitAll = tDamagePlayer->_gethitall();

		_getHit = tDamagePlayer->_gethit();
		_getHitBS = tDamagePlayer->_gethitbs();
		_getHitMissed = tDamagePlayer->_gethitmissed();
		_getHitMissedReal = tDamagePlayer->_gethitmissedreal();
		_enlightenSum = tDamagePlayer->_enlightensum();

		_gigaEnlightenProc = tDamagePlayer->_gigaenlightenproc();
		_teraEnlightenProc = tDamagePlayer->_teraenlightenproc();
		_skillCounts = tDamagePlayer->_skillcounts();
		_dodgeCounts = tDamagePlayer->_dodgecounts();
		_deathCounts = tDamagePlayer->_deathcounts();

		_historyAvgAB = tDamagePlayer->_historyavgab();
		_historyAvgBD = tDamagePlayer->_historyavgbd();
		_historygear90 = tDamagePlayer->_historygear90();
		_historygear50 = tDamagePlayer->_historygear50();
		_historyacc01 = tDamagePlayer->_historyacc01();

		_historyacc02 = tDamagePlayer->_historyacc02();
		_historyLosedHP = tDamagePlayer->_historylosedhp();
		_JqStack = tDamagePlayer->_jqstack();
		_historyABTime = tDamagePlayer->_historyabtime();

		_historyAggroTime = tDamagePlayer->_historyaggrotime();

		_historyAvgAS = tDamagePlayer->_historyavgas();
		_historyASTime = tDamagePlayer->_historyastime();
	}
};