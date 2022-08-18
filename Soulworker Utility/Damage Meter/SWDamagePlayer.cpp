#include "pch.h"
#include ".\Damage Meter\SWDamageMonster.h"
#include ".\Damage Meter\SWDamagePlayer.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\PacketInfo.h"

SWDamagePlayer::SWDamagePlayer(UINT32 id, UINT64 totalDMG, UINT64 soulstoneDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, USHORT maxCombo, UINT32 monsterID, UINT32 skillID) {
	_id = id;
	AddDamage(totalDMG, soulstoneDMG, damageType, maxCombo, monsterID, skillID);
}

SWDamagePlayer::SWDamagePlayer(UINT32 id) {
	_id = id;
}

SWDamagePlayer::~SWDamagePlayer() {

	for (auto itr = _monsterInfo.begin(); itr != _monsterInfo.end(); itr++) {
		delete (*itr);
	}

	_monsterInfo.clear();
}

BOOL SWDamagePlayer::SortFunction(SWDamagePlayer* playerA, SWDamagePlayer* playerB) {
	return playerA->GetDamage() > playerB->GetDamage();
}

VOID SWDamagePlayer::InsertMonsterInfo(UINT32 monsterID,UINT32 db2, UINT64 damage, UINT64 critDamage, USHORT hitCount, USHORT critHitCount, UINT32 skillID) {

	auto itr = _monsterInfo.begin();



	for (; itr != _monsterInfo.end(); itr++) {
		if (db2 == (*itr)->GetDB2()) {
			(*itr)->AddDamage(damage, critDamage, hitCount, critHitCount, skillID);
			return;
		}
	}

	_monsterInfo.push_back(new SWDamageMonster(monsterID, db2, damage, critDamage, hitCount, critHitCount, skillID));
}

VOID SWDamagePlayer::Sort() {
	sort(_monsterInfo.begin(), _monsterInfo.end(), SWDamageMonster::SortFunction);
}

VOID SWDamagePlayer::AddDamage(UINT64 totalDMG, UINT64 soulstoneDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, USHORT maxCombo, UINT32 monsterID, UINT32 skillID)
{
	//LogInstance.WriteLog("[PLAYER %u (%s)] [totalDMG %u] [monsterID %u]", _id,DAMAGEMETER.GetPlayerName(_id),totalDMG,monsterID);


	// db부분 임의로 추가함
	SW_DB2_STRUCT* db = DAMAGEMETER.GetMonsterDB(monsterID);
	UINT32 db2 = 0;
	if (db != nullptr) {
		db2 = db->_db2;
	}

	// 악세셋옵 계산용
	if (!damageType.MISS && _id == DAMAGEMETER.GetMyID()) {
		auto metadata = DAMAGEMETER.GetPlayerMetaData(_id);
		if (metadata != nullptr) {
			metadata->HitEnemy();
		}
	}

	_hitCount += 1;
	_critHitCount += damageType.CRIT;
	// 옥타곤 같은게 아니라면 치확 계산에 포함 (소울스톤 데미지는 밑에 잡몹도 제외한 버전에서 포함함)
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

	USHORT worldID = DAMAGEMETER.GetWorldID();

	// 화이트리스트 제도
	// 브세일 경우 보스몹만 데미지에 추가함
	BOOL bypassCheck = false;
	// BS
	if (worldID == 21018) {
		if (db2 == 31310101 || db2 == 31310102) {
			_damage += totalDMG;
			_soulstoneDamage += soulstoneDMG;
			_damageForSoulstone += totalDMG;
			_soulstoneDamageForSoulstone += soulstoneDMG;
		}
		else
		{
			//LogInstance.WriteLog("Rejected monster %u in 21018", db2);
		}
	}
	// BS Solo
	else if (worldID == 24018) {
		if (db2 == 32320101 || db2 == 32320102) {
			_damage += totalDMG;
			_soulstoneDamage += soulstoneDMG;
			_damageForSoulstone += totalDMG;
			_soulstoneDamageForSoulstone += soulstoneDMG;
		}
		else
		{
			//LogInstance.WriteLog("Rejected monster %u in 24018", db2);
		}
	}
	// 이하 블랙리스트 제도
	// 제외목록에 들어가있지 않다면 데미지 합산
	else if (dpsIgnoreIdList.find(db2) == dpsIgnoreIdList.end() && db->_type != 6) {
		_damage += totalDMG;
		_soulstoneDamage += soulstoneDMG;

		if (totalDMG >= 200 && (damageType.soulstoneType != 0)) {
			_damageForSoulstone += totalDMG;
			_soulstoneDamageForSoulstone += soulstoneDMG;
		}
	}
#if DEBUG_DAMAGE_PLAYER == 1
	else if (db->_type == 6)
	{

		LogInstance.WriteLog("Ignored damage to %d, type 6",db2);

	}
	LogInstance.WriteLog("[PLAYER] [ID = %d] [DMG = %llu] [hitCount = %d] [cirtHitCount = %d] [maxCombo = %d]", _id, _damage, _hitCount, _critHitCount, _maxCombo);
#endif

	InsertMonsterInfo(monsterID,db2, totalDMG, soulstoneDMG, 1, damageType.CRIT, skillID);
	Sort();
}

UINT32 SWDamagePlayer::GetID() {
	return _id;
}

UINT64 SWDamagePlayer::GetDamage() {
	return _damage;
}

UINT64 SWDamagePlayer::GetSoulstoneDamage() {
	return _soulstoneDamage;
}

USHORT SWDamagePlayer::GetHitCount() {
	return _hitCount;
}

USHORT SWDamagePlayer::GetCritHitCount() {
	return _critHitCount;
}

USHORT SWDamagePlayer::GetMaxCombo() {
	return _maxCombo;
}

UINT64 SWDamagePlayer::GetMonsterTotalDamage() {

	UINT64 monsterTotalDamage = 0;

	for (auto itr = _monsterInfo.begin(); itr != _monsterInfo.end(); itr++)
		monsterTotalDamage += (*itr)->GetDamage();

	return monsterTotalDamage;
}

USHORT SWDamagePlayer::GetHitCountForCritRate()
{
	return _hitCountForCritRate;
}

USHORT SWDamagePlayer::GetCritHitCountForCritRate()
{
	return _critHitCountForCritRate;
}

USHORT SWDamagePlayer::GetSoulstoneCount()
{
	return _soulstoneCount;
}

UINT64 SWDamagePlayer::GetDamageForSoulstone()
{
	return _damageForSoulstone;
}

UINT64 SWDamagePlayer::GetSoulStoneDamageForSoulstone()
{
	return _soulstoneDamageForSoulstone;
}

USHORT SWDamagePlayer::GetGetHitAll()
{
	return _getHitAll;
}

USHORT SWDamagePlayer::GetGetHit()
{
	return _getHit;
}

USHORT SWDamagePlayer::GetGetHitBS()
{
	return _getHitBS;
}

USHORT SWDamagePlayer::GetGetHitMissed()
{
	return _getHitMissed;
}

USHORT SWDamagePlayer::GetGetHitMissedReal()
{
	return _getHitMissedReal;
}

USHORT SWDamagePlayer::GetMissCount()
{
	return _missCount;
}

std::vector<SWDamageMonster*>::const_iterator SWDamagePlayer::GetMonsterInfo(UINT id) {

	auto itr = _monsterInfo.begin();

	for (; itr != _monsterInfo.end(); itr++) {
		if ((*itr)->GetID() == id) {
			return itr;
		}
	}

	return itr;
}

VOID SWDamagePlayer::SetHistoryAvgAB(DOUBLE historyAvgAB)
{
	_historyAvgAB = historyAvgAB;
}
VOID SWDamagePlayer::SetHistoryAvgBD(DOUBLE historyAvgBD)
{
	_historyAvgBD = historyAvgBD;
}
DOUBLE SWDamagePlayer::GetHistoryAvgAB()
{
	return _historyAvgAB;
}
DOUBLE SWDamagePlayer::GetHistoryAvgBD()
{
	return _historyAvgBD;
}

FLOAT SWDamagePlayer::GetEnlightenSum()
{
	return _enlightenSum;
}

USHORT SWDamagePlayer::GetGigaEnlighten()
{
	return _gigaEnlightenProc;
}

USHORT SWDamagePlayer::GetTeraEnlighten()
{
	return _teraEnlightenProc;
}

VOID SWDamagePlayer::setHistoryBS(int type, DOUBLE value)
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

DOUBLE SWDamagePlayer::GetHistoryBS(int type)
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
	default:
		return 0;
	}
}

VOID SWDamagePlayer::setHistoryLosedHP(DOUBLE losedHP)
{
	_historyLosedHP = losedHP;
}

DOUBLE SWDamagePlayer::GetHistoryLosedHP()
{
	return _historyLosedHP;
}
VOID SWDamagePlayer::SetHistoryABTime(DOUBLE historyABTime)
{
	_historyABTime = historyABTime;
}
DOUBLE SWDamagePlayer::GetHistoryABTime()
{
	return _historyABTime;
}
VOID SWDamagePlayer::AddSkillUsed(UINT32 skillId)
{
	if (DAMAGEMETER.isHistoryMode())
		return;

	_skillCounts++;

	BOOL isInFullAB = false;
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

VOID SWDamagePlayer::AddDodgeUsed()
{
	_dodgeCounts++;
}

VOID SWDamagePlayer::AddDeathCount()
{
	_deathCounts++;
}

VOID SWDamagePlayer::AddGetDamage(UINT64 totalDMG, SWPACKETDAMAGE_DAMAGETYPE damageType, UINT32 monsterID, UINT32 skillID)
{
	_getHitAll++;
	if (totalDMG > 0) {
		_getHit++;
		// 검은 장판, 미니종복의 종복 (둘다 경직 없음)
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

VOID SWDamagePlayer::AddEnlighten(FLOAT value)
{
	_enlightenSum += value;
	if (value == 5.0) {
		_gigaEnlightenProc++;
	}
	else if (value == 10.0) {
		_teraEnlightenProc++;
	}
}

USHORT SWDamagePlayer::GetSkillUsed()
{
	return _skillCounts;
}

USHORT SWDamagePlayer::GetDodgeUsed()
{
	return _dodgeCounts;
}

USHORT SWDamagePlayer::GetDeathCount()
{
	return _deathCounts;
}

VOID SWDamagePlayer::SetJqStack(BYTE stack)
{
	_JqStack = stack;
}

BYTE SWDamagePlayer::GetJqStack() {
	return _JqStack;
}


std::vector<SWDamageMonster*>::const_iterator SWDamagePlayer::begin() {
	return _monsterInfo.begin();
}

std::vector<SWDamageMonster*>::const_iterator SWDamagePlayer::end() {
	return _monsterInfo.end();
}

const SIZE_T& SWDamagePlayer::size() {
	return _monsterInfo.size();
}
