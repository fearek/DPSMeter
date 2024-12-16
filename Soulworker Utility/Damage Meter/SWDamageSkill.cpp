#include "pch.h"
#include ".\Damage Meter\SWDamageSkill.h"

SWDamageSkill::SWDamageSkill(uint32_t id, uint64_t damage, uint64_t critDamage, unsigned short hitCount, unsigned short critHitCount){
	_id = id;
	_damage = damage;
	_critDamage = critDamage;
	_hitCount = hitCount;
	_critHitCount = critHitCount;

	SetNameFromDB();

#if DEBUG_DAMAGE_SKILL == 1
	LogInstance.WriteLog("\t\t[SKILL] [ID = %d] [NAME = %s] [DMG = %llu] [cirDMG = %llu] [hitCount = %d] [cirtHitCount = %d]", _id, _name,_damage, _critDamage, _hitCount, _critHitCount);
#endif
}

void SWDamageSkill::SetNameFromDB()
{
	ZeroMemory(_name, SKILL_NAME_LEN);
	SWDB.GetSkillName(_id, _name, SKILL_NAME_LEN);
}

bool SWDamageSkill::SortFunction(SWDamageSkill* skillA, SWDamageSkill* skillB) {
	return skillA->GetDamage() > skillB->GetDamage();
}

void SWDamageSkill::AddDamage(uint64_t damage, uint64_t critDamage, unsigned short hitCount, unsigned short critHitCount) {
	_damage += damage;
	_critDamage += critDamage;
	_hitCount += hitCount;
	_critHitCount += critHitCount;

#if DEBUG_DAMAGE_SKILL == 1
	LogInstance.WriteLog("\t\t[SKILL] [ID = %d] [NAME = %s] [DMG = %llu] [cirDMG = %llu] [hitCount = %d] [cirtHitCount = %d]", _id, _name, _damage, _critDamage, _hitCount, _critHitCount);
#endif
}

uint32_t SWDamageSkill::GetID() {
	return _id;
}

uint64_t SWDamageSkill::GetDamage() {
	return _damage;
}

uint64_t SWDamageSkill::GetCritDamage() {
	return _critDamage;
}

unsigned short SWDamageSkill::GetHitCount() {
	return _hitCount;
}

unsigned short SWDamageSkill::GetCritHitCount() {
	return _critHitCount;
}

unsigned short SWDamageSkill::GetSkillUsed()
{
	return _skillCasts;
}

char* SWDamageSkill::GetName() {
	return _name;
}
