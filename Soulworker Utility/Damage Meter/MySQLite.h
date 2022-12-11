#pragma once
#include "Third Party\SQLite\include\sqlite3.h"

#define SWDB MySQL::getInstance()
#define SWDBPATH "SWDB.db"

#ifdef _DEBUG
#define DEBUG_SKILL_NAME 0
#define DEBUG_MONSTER_NAME 0
#endif

class MySQL : public Singleton<MySQL> {
private:
	sqlite3* _db;
	sqlite3* _memdb;

	BOOL InitDB();
	BOOL InitMemDB();
	VOID FreeDB();

	BOOL InitSkillDB();
	BOOL InitMonsterDB();
	BOOL InitMapDB();
	BOOL InitBuffDB();
	BOOL InitSkillTimelineDB();
	BOOL InitBuffTimelineDB();

	sqlite3_stmt* _skill_stmt;
	sqlite3_stmt* _monster_stmt;
	sqlite3_stmt* _map_stmt;
	sqlite3_stmt* _map_stmt_eng;
	sqlite3_stmt* _buff_stmt;

public:
	MySQL();
	~MySQL();
	std::map<unsigned int, std::string> stats =
	{
		{1, "CURRENT_HEALTH" },
		{2, "CURRENT_SG" },
		{3,"CURRENT_STAMINA"},
		{4,"STR"},
		{5,"DEX"},
		{6,"INTELLIGENCE"}, //whatever the fuck these are
		{7,"BALANCE"},
		{8,"CON"},
		{9,"LUK"},
		{10,"HEALTH"},
		{11,"HEALTH_REGEN"},
		{12,"MAX_SG"},
		{13,"SG_REGEN"},
		{14,"STAMINA_MAX"},
		{15,"STAMINA_REGEN"},
		{16,"CURRENT_SOULVAPOR"},
		{17,"MAX_SOULVAPOR"},
		{18,"MOVE_SPEED"},
		{19,"ATTACK_SPEED"},
		{20,"ATTACK_MIN"},
		{21,"ATTACK_MAX"},
		{24,"DEFENCE"},
		{25,"MAGIC_DEFENCE"},
		{26,"ACCURACY"},
		{27,"MAGIC_ACCURACY"},
		{28,"PARTIAL_DAMAGE"},
		{29,"CRIT_CHANCE"},
		{30,"MAGIC_CRIT"},
		{31,"CRIT_RESIST"},
		{32,"MAGIC_CRIT_RESIST"},
		{35,"CRIT_DAMAGE"},
		{38,"DAMAGE_REDUCTION"},
		{39,"MAGIC_DAMAGE_REDUCTION"},
		{43,"EVASION"},
		{44,"MAGIC_EVASION"},
		{47,"ARMOR_BREAK"},
		{48,"MAGIC_ARMOR_BREAK"},
		{49,"FIRE_RESISTANCE"},
		{50,"POISEN_RESISTANCE"},
		{51,"ELECTRIC_RESISTANCE"},
		{52,"BLEED_RESISTANCE"},
		{53,"STUN_RESISTANCE"},
		{54,"PARALYSIS_RESISTANCE"},
		{55,"SLEEP_RESISTANCE"},
		{56,"FROZEN_RESISTANCE"},
		{57,"SILENCE_RESISTANCE"},
		{58,"VULN_RESISTANCE"},
		{59,"FASCINATION_RESISTANCE"},
		{60,"CONFUSED_RESISTANCE"},
		{63,"LIGHT_DAMAGE"},
		{64,"SPITE_DAMAGE"},
		{65,"GRACE_DAMAGE"},
		{66,"HATRED_DAMAGE"},
		{67,"CURE_DAMAGE"},
		{68,"TORMENT_DAMAGE"},
		{69,"LIGHT_RESISTANCE"},
		{70,"SPITE_RESISTANCE"},
		{71,"GRACE_RESISTANCE"},
		{72,"HATRED_RESISTANCE"},
		{73,"CURE_RESISTANCE"},
		{74,"TORMENT_RESISTANCE"},
		{75,"MANIAC_DAMAGE"},
		{76,"MANIAC_BALANCE"},
		{255,"IF_VICTORY_HP_REGEN"}
	};
	std::string GetStatName(unsigned int statid)
	{
		if (stats.find(statid) == stats.end())
		{
			return std::to_string(statid);
		}
		else
		{
			return stats.at(statid);
		}
	}
	BOOL Init();
	BOOL GetSkillName(UINT32 skillId, _Out_ CHAR* out_buffer, _In_ SIZE_T out_buffer_length);
	BOOL GetMonsterName(UINT32 DB2, _Out_ CHAR* out_buffer, _In_ SIZE_T out_buffer_length);
	BOOL GetMonsterType(UINT32 DB2, INT32* type);
	BOOL GetMapName(UINT32 mapId, _Out_ CHAR* out_buffer, _In_ SIZE_T out_buffer_length);
	BOOL GetMapNameENG(UINT32 mapId, _Out_ CHAR* out_buffer, _In_ SIZE_T out_buffer_length);
	BOOL GetBuffName(UINT32 buffId, _Out_ CHAR* out_buffer, _In_ SIZE_T out_buffer_length, _Out_ CHAR* out_buffer_desc = NULL, _In_ SIZE_T out_buffer_desc_length = NULL);
};