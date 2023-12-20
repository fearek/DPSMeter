#include "pch.h"
#include ".\Damage Meter\SWDamageMonster.h"
#include ".\Damage Meter\SWDamagePlayer.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\PacketInfo.h"
#include ".\MySQLite.h"
#include ".\UI\Option.h"

SWDamagePlayer::SWDamagePlayer(uint32_t id, uint64_t totalDMG, uint64_t soulstoneDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, uint16_t maxCombo, uint32_t monsterID, uint32_t skillID) {
	_id = id;
	AddDamage(totalDMG, soulstoneDMG, damageType, maxCombo, monsterID, skillID);
}

SWDamagePlayer::SWDamagePlayer(uint32_t id) {
	_id = id;
}

SWDamagePlayer::~SWDamagePlayer() {

	for (auto itr = _monsterInfo.begin(); itr != _monsterInfo.end(); itr++) {
		delete (*itr);
	}
	_monsterInfo.clear();

	for (auto itr = skillCounts.begin(); itr != skillCounts.end(); itr++)
		delete itr->second;

	skillCounts.clear();
}

bool SWDamagePlayer::SortFunction(SWDamagePlayer* playerA, SWDamagePlayer* playerB) {
	return playerA->GetDamage() > playerB->GetDamage();
}

void SWDamagePlayer::InsertMonsterInfo(uint32_t monsterID, uint64_t damage, uint64_t critDamage, uint16_t hitCount, uint16_t critHitCount, uint32_t skillID) {

	auto itr = _monsterInfo.begin();

	SW_DB2_STRUCT* db = DAMAGEMETER.GetMonsterDB(monsterID);
	//LogInstance.WriteLog(const_cast<LPTSTR>(_T("[Monster] [MonsterID = %d] [DB2 = %d]")), monsterID, db->_db2);

	uint32_t db2 = 0;

	if (db != nullptr) {
		db2 = db->_db2;
	}

	for (; itr != _monsterInfo.end(); itr++) {
		if (db2 == (*itr)->GetDB2()) {
			(*itr)->AddDamage(damage, critDamage, hitCount, critHitCount, skillID);
			return;
		}
	}

	_monsterInfo.push_back(new SWDamageMonster(monsterID, db2, damage, critDamage, hitCount, critHitCount, skillID));
}

void SWDamagePlayer::Sort() {
	sort(_monsterInfo.begin(), _monsterInfo.end(), SWDamageMonster::SortFunction);
}

void SWDamagePlayer::AddDamage(uint64_t totalDMG, uint64_t soulstoneDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, uint16_t maxCombo, uint32_t monsterID, uint32_t skillID)
{
	//LogInstance.WriteLog(const_cast<LPTSTR>(_T("[PLAYER] [DamageType = %d]")), damageType.CRIT);

	if (DAMAGEMETER.isHistoryMode())
		return;

	// Skip not in db monster
	SW_DB2_STRUCT* db = DAMAGEMETER.GetMonsterDB(monsterID);
	uint32_t db2 = 0;
	if (db == nullptr) {
		return;
	}
	db2 = db->_db2;

	// 
	if (!damageType.MISS && _id == DAMAGEMETER.GetMyID()) {
		auto metadata = DAMAGEMETER.GetPlayerMetaData(_id);
		if (metadata != nullptr) {
			metadata->HitEnemy();
		}
	}

	_hitCount += 1;
	_critHitCount += damageType.CRIT;
	// 
	if (totalDMG >= 200) {
		_hitCountForCritRate += 1;
		_critHitCountForCritRate += damageType.CRIT;
		_missCount += damageType.MISS;
		/*
		if (damageType.soulstoneType) {
			_soulstoneCount++;
		}
		*/
		if (soulstoneDMG != 0) {
			_soulstoneCount++;
		}

	}
	if (maxCombo > _maxCombo) {
		_maxCombo = maxCombo;
	}

	uint16_t worldID = DAMAGEMETER.GetWorldID();

	auto stList = StrictModeList.find(worldID);
	bool isStrictMode = false;
	if (stList != StrictModeList.end())
	{
		auto& vec = (*stList).second;
		auto find = std::find(vec.begin(), vec.end(), db2);
		if (find == vec.end())
			return;
		isStrictMode = true;
	}
	// Ignore object
	if (isStrictMode || (!isStrictMode && dpsIgnoreIdList.find(db2) == dpsIgnoreIdList.end() && db->_type != 6)) {
		_damage += totalDMG;
		_soulstoneDamage += soulstoneDMG;

		if (totalDMG >= 200 && (damageType.soulstoneType != 0)) {
			_damageForSoulstone += totalDMG;
			_soulstoneDamageForSoulstone += soulstoneDMG;
		}
	}

#if DEBUG_DAMAGE_PLAYER == 1
	LogInstance.WriteLog(const_cast<LPTSTR>(_T("[PLAYER] [ID = %d] [MonsterID = %04x] [DMG = %llu] [hitCount = %d] [cirtHitCount = %d] [maxCombo = %d]")), _id, monsterID, _damage, _hitCount, _critHitCount, _maxCombo);
#endif

	InsertMonsterInfo(monsterID, totalDMG, soulstoneDMG, 1, damageType.CRIT, skillID);
	Sort();
}

uint32_t SWDamagePlayer::GetID() {
	return _id;
}

uint64_t SWDamagePlayer::GetDamage() {
	return _damage;
}

uint64_t SWDamagePlayer::GetSoulstoneDamage() {
	return _soulstoneDamage;
}

uint16_t SWDamagePlayer::GetHitCount() {
	return _hitCount;
}

uint16_t SWDamagePlayer::GetCritHitCount() {
	return _critHitCount;
}

uint16_t SWDamagePlayer::GetMaxCombo() {
	return _maxCombo;
}

uint64_t SWDamagePlayer::GetMonsterTotalDamage() {

	uint64_t monsterTotalDamage = 0;

	for (auto itr = _monsterInfo.begin(); itr != _monsterInfo.end(); itr++)
		monsterTotalDamage += (*itr)->GetDamage();

	return monsterTotalDamage;
}

uint16_t SWDamagePlayer::GetHitCountForCritRate()
{
	return _hitCountForCritRate;
}

uint16_t SWDamagePlayer::GetCritHitCountForCritRate()
{
	return _critHitCountForCritRate;
}

uint16_t SWDamagePlayer::GetSoulstoneCount()
{
	return _soulstoneCount;
}

uint64_t SWDamagePlayer::GetDamageForSoulstone()
{
	return _damageForSoulstone;
}

uint64_t SWDamagePlayer::GetSoulStoneDamageForSoulstone()
{
	return _soulstoneDamageForSoulstone;
}

uint16_t SWDamagePlayer::GetGetHitAll()
{
	return _getHitAll;
}

uint16_t SWDamagePlayer::GetGetHit()
{
	return _getHit;
}

uint16_t SWDamagePlayer::GetGetHitBS()
{
	return _getHitBS;
}

uint16_t SWDamagePlayer::GetGetHitMissed()
{
	return _getHitMissed;
}

uint16_t SWDamagePlayer::GetGetHitMissedReal()
{
	return _getHitMissedReal;
}

uint16_t SWDamagePlayer::GetMissCount()
{
	return _missCount;
}

std::vector<SWDamageMonster*>::const_iterator SWDamagePlayer::GetMonsterInfo(unsigned int id) {

	auto itr = _monsterInfo.begin();

	for (; itr != _monsterInfo.end(); itr++) {
		if ((*itr)->GetID() == id) {
			return itr;
		}
	}

	return itr;
}

double SWDamagePlayer::GetHistoryABTime()
{
	return _historyABTime;
}

void SWDamagePlayer::SetHistoryABTime(double historyABTime)
{
	_historyABTime = historyABTime;
}

void SWDamagePlayer::SetHistoryAvgAB(double historyAvgAB)
{
	_historyAvgAB = historyAvgAB;
}

double SWDamagePlayer::GetHistoryAvgAB()
{
	return _historyAvgAB;
}

void SWDamagePlayer::SetHistoryAvgBD(double historyAvgBD)
{
	_historyAvgBD = historyAvgBD;
}

double SWDamagePlayer::GetHistoryAvgBD()
{
	return _historyAvgBD;
}

double SWDamagePlayer::GetHistoryAggroTime()
{
	return _historyAggroTime;
}

void SWDamagePlayer::SetHistoryAggroTime(double t)
{
	_historyAggroTime = t;
}

double SWDamagePlayer::GetHistoryASTime()
{
	return _historyASTime;
}

void SWDamagePlayer::SetHistoryASTime(double d)
{
	_historyASTime = d;
}

void SWDamagePlayer::SetHistoryAvgAS(double d)
{
	_historyAvgAS = d;
}

double SWDamagePlayer::GetHistoryAvgAS()
{
	return _historyAvgAS;
}

float SWDamagePlayer::GetEnlightenSum()
{
	return _enlightenSum;
}

uint16_t SWDamagePlayer::GetGigaEnlighten()
{
	return _gigaEnlightenProc;
}

uint16_t SWDamagePlayer::GetTeraEnlighten()
{
	return _teraEnlightenProc;
}

void SWDamagePlayer::setHistoryBS(int type, double value)
{
	switch (type) {
	case 90:
		_historygear90 = value;
		break;
	case 50:
		_historygear50 = value;
		break;
	case 1:
		_historyacc01 = value;
		break;
	case 2:
		_historyacc02 = value;
		break;

	}
}

double SWDamagePlayer::GetHistoryBS(int type)
{
	switch (type) {
	case 90:
		return _historygear90;
	case 50:
		return _historygear50;
	case 1:
		return _historyacc01;
	case 2:
		return _historyacc02;
	}
	return 0;
}

void SWDamagePlayer::setHistoryLosedHP(double losedHP)
{
	_historyLosedHP = losedHP;
}

double SWDamagePlayer::GetHistoryLosedHP()
{
	return _historyLosedHP;
}

void SWDamagePlayer::AddSkillUsed(uint32_t skillId)
{
	if (DAMAGEMETER.isHistoryMode())
		return;

	_skillCounts++;

	bool isInFullAB = false;
	auto metadata = DAMAGEMETER.GetPlayerMetaData(_id);
	if (metadata != nullptr) {
		isInFullAB = metadata->_fullABStarted;
	}

	if (skillCounts.find(skillId) == skillCounts.end()) {
		SkillCount* pSc = new SkillCount;
		pSc->_count = 1;
		pSc->_in_full_ab_count = (isInFullAB ? 1 : 0);

		skillCounts.insert({ skillId, pSc });
		return;
	}

	SkillCount* pSc = skillCounts[skillId];
	pSc->_count += 1;
	if (isInFullAB)
		pSc->_in_full_ab_count += 1;
}

void SWDamagePlayer::AddDodgeUsed()
{
	_dodgeCounts++;
}

void SWDamagePlayer::AddDeathCount()
{
	_deathCounts++;
}

void SWDamagePlayer::AddGetDamage(uint64_t totalDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, uint32_t monsterID, uint32_t skillID)
{
	_getHitAll++;
	if (totalDMG > 0) {
		_getHit++;
		// 검은 장판, 미니종복의 중복 (둘다 경직 없음)
		// Tenebris black water and unk
		if (skillID != 1313101016 && skillID != 1313101113) {
			_getHitBS++;
		}

		if (damageType.MISS) {
			_getHitMissedReal++;
		}
	}

	if (damageType.MISS) {
		_getHitMissed++;
	}
}

void SWDamagePlayer::AddEnlighten(float value)
{
	_enlightenSum += value;
	if (value == 5.0) {
		_gigaEnlightenProc++;
	}
	else if (value == 10.0) {
		_teraEnlightenProc++;
	}
}

uint16_t SWDamagePlayer::GetSkillUsed()
{
	return _skillCounts;
}

uint16_t SWDamagePlayer::GetDodgeUsed()
{
	return _dodgeCounts;
}

uint16_t SWDamagePlayer::GetDeathCount()
{
	return _deathCounts;
}

void SWDamagePlayer::SetJqStack(uint8_t stack)
{
	_JqStack = stack;
}

uint8_t SWDamagePlayer::GetJqStack() {
	return _JqStack;
}


std::vector<SWDamageMonster*>::const_iterator SWDamagePlayer::begin() {
	return _monsterInfo.begin();
}

std::vector<SWDamageMonster*>::const_iterator SWDamagePlayer::end() {
	return _monsterInfo.end();
}

const SIZE_T SWDamagePlayer::size() {
	return _monsterInfo.size();
}