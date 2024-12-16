#pragma once
#include "pch.h"
#include ".\Third Party\FlatBuffers\include\SW_HISTORY_.h"
#include ".\Damage Meter\MySQLite.h"


using namespace SoulMeterFBS::History;

#define DEBUG_DAMAGE_SKILL 0
#define SKILL_NAME_LEN 64

class SWDamageSkill : public MemoryPool<SWDamageSkill, 100> {
private:
	uint32_t _id;
	uint64_t _damage;
	uint64_t _critDamage;
	unsigned short _hitCount;
	unsigned short _critHitCount;
	unsigned short _skillCasts;
	char _name[SKILL_NAME_LEN];

public:
	SWDamageSkill() : _id(0), _damage(0), _critDamage(0), _hitCount(0), _critHitCount(0), _skillCasts(0) { }
	SWDamageSkill(uint32_t id, uint64_t damage, uint64_t critDamage, unsigned short hitCount, unsigned short critHitCount);
	~SWDamageSkill() {}

	static bool SortFunction(SWDamageSkill* skillA, SWDamageSkill* skillB);

	uint32_t GetID();
	uint64_t GetDamage();
	uint64_t GetCritDamage();
	unsigned short GetHitCount();
	unsigned short GetCritHitCount();
	unsigned short GetSkillUsed();
	char* GetName();

	void SetNameFromDB();
	void AddDamage(uint64_t damage, uint64_t critDamage, unsigned short hitCount, unsigned short critHitCount);

	void Serialization(flatbuffers::FlatBufferBuilder& fbb, std::vector<flatbuffers::Offset<_tDamageSkill>>& vDamageSkill)
	{
		_tDamageSkillBuilder tdsb(fbb);

		tdsb.add__id(GetID());
		tdsb.add__damage(GetDamage());
		tdsb.add__critdamage(GetCritDamage());
		tdsb.add__hitcount(GetHitCount());
		tdsb.add__crithitcount(GetCritHitCount());
		tdsb.add__skillcasts(GetSkillUsed());

		vDamageSkill.push_back(tdsb.Finish());
	}

	void UnSerialization(const _tDamageSkill* tDamageSkill)
	{
		_id = tDamageSkill->_id();
		_damage = tDamageSkill->_damage();
		_critDamage = tDamageSkill->_critdamage();
		_hitCount = tDamageSkill->_hitcount();
		_critHitCount = tDamageSkill->_crithitcount();
		_skillCasts = tDamageSkill->_skillcasts();

		SetNameFromDB();
	}
};