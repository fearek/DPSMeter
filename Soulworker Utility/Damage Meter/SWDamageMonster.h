#pragma once
#include ".\Damage Meter\SWDamageSkill.h"


#define DEBUG_DAMAGE_MONSTER 0
#define MONSTER_NAME_LEN 64

class SWDamageMonster : public MemoryPool<SWDamageMonster, 100> {
private:
	UINT32 _id;
	//USHORT _db1;
	UINT32 _db2;
	UINT64 _damage;
	UINT64 _critDamage;
	USHORT _hitCount;
	USHORT _critHitCount;
	INT32 _type;
	CHAR _name[MONSTER_NAME_LEN];

	std::vector<SWDamageSkill*> _skillinfo;

	VOID InsertSkillInfo(UINT32 skillID, UINT64 damage, UINT64 critDamage, USHORT hitCount, USHORT critHitCount);
	VOID Sort();

protected:
	SWDamageMonster() :_type(-1), _id(0), _db2(0), _damage(0), _critDamage(0), _hitCount(0), _critHitCount(0) { }

public:
	SWDamageMonster(UINT32 id, UINT32 db2, UINT64 damage, UINT64 critDamage, USHORT hitCount, USHORT critHitCount, UINT32 skillID);
	~SWDamageMonster();

	static BOOL SortFunction(SWDamageMonster* monsterA, SWDamageMonster* monsterB);

	UINT32 GetID();
	INT32 GetType();
	//USHORT GetDB1();
	UINT32 GetDB2();
	UINT64 GetDamage();
	UINT64 GetCritDamage();
	USHORT GetHitCount();
	USHORT GetCritHitCount();
	UINT64 GetSkillTotalDamage();
	const CHAR* GetName();

	std::vector<SWDamageSkill*>::const_iterator begin();
	std::vector<SWDamageSkill*>::const_iterator end();
	const SIZE_T& size();


	VOID AddDamage(UINT64 damage, UINT64 critDamage, USHORT hitCount, USHORT critHitCount, UINT32 skillID);
};