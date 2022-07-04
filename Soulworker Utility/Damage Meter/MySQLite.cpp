#include "pch.h"
#include ".\Language\Region.h"
#include ".\Damage Meter\MySQLite.h"
#include <map>
MySQL::MySQL() : _db(nullptr), _memdb(nullptr) {

}

MySQL::~MySQL() {
	FreeDB();
}

BOOL MySQL::InitDB(){

	if (sqlite3_open(SWDBPATH, &_db) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitDB : %s", sqlite3_errmsg(_db));
		sqlite3_close(_db);
		_db = nullptr;

		return FALSE;
	}

	return TRUE;
}

BOOL MySQL::InitMemDB() {

	if (sqlite3_open(":memory:", &_memdb) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitMemDB : %s", sqlite3_errmsg(_memdb));
		sqlite3_close(_memdb);
		_memdb = nullptr;

		return FALSE;
	}

	return TRUE;
}

VOID MySQL::FreeDB() {

	if (_db != nullptr) {
		sqlite3_close(_db);
		_db = nullptr;
	}

	if (_memdb != nullptr) {
		sqlite3_close(_memdb);
		_memdb = nullptr;
	}

	if (_skill_stmt != nullptr) {
		sqlite3_finalize(_skill_stmt);
		_skill_stmt = nullptr;
	}

	if (_monster_stmt != nullptr) {
		sqlite3_finalize(_monster_stmt);
		_monster_stmt = nullptr;
	}

}

BOOL MySQL::InitSkillDB() {

	CHAR* errbuf = nullptr;

	const CHAR* sql = "CREATE TABLE IF NOT EXISTS Skill(Id INTEGER PRIMARY KEY, Name_KR TEXT NOT NULL);";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitSkillDB : %s", errbuf);
		sqlite3_free(errbuf);

		return FALSE;
	}

//	const CHAR* sql2 = "SELECT Name From Skill Where Id = ?";
	std::string lang = Language.GetLanguageNameUsedForSQLite();
	std::string sql2 = std::string("SELECT Name_") + std::string(lang) + " From Skill Where Id = ?";

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_skill_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 : %s", sqlite3_errmsg(_db));

		return FALSE;
	}

	return TRUE;
}

BOOL MySQL::InitMonsterDB() {

	CHAR* errbuf = nullptr;

	//const CHAR* sql = "CREATE TABLE IF NOT EXISTS Monster(Db1 INTEGER, Db2 INTEGER, Name_KR TEXT NOT NULL, PRIMARY KEY(Db1, Db2));";
	const CHAR* sql = "CREATE TABLE IF NOT EXISTS Monster(Db2 INTEGER, Name_KR TEXT NOT NULL, PRIMARY KEY(Db2));";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitMonsterDB : %s", errbuf);
		sqlite3_free(errbuf);

		return FALSE;
	}

	//std::string sql2 = "SELECT Name_" LANG " From Monster Where Db1 = ? and Db2 = ?";
	std::string lang = Language.GetLanguageNameUsedForSQLite();
	std::string sql2 = "SELECT Name_" + lang + " From Monster Where Db2 = ?"; //msvc doesnt like defines in + operator of std::string

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_monster_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 : %s", sqlite3_errmsg(_db));

		return FALSE;
	}

	return TRUE;
}

BOOL MySQL::InitMapDB() {
	CHAR* errbuf = nullptr;

	const CHAR* sql = "CREATE TABLE IF NOT EXISTS Map(Id INTEGER PRIMARY KEY, Name_KR TEXT NOT NULL);";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitMapDB : %s", errbuf);
		sqlite3_free(errbuf);

		return FALSE;
	}
	std::string lang = Language.GetLanguageNameUsedForSQLite();
	std::string sql2 = "SELECT Name_" + lang +" From Map Where Id = ?";

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_map_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 : %s", sqlite3_errmsg(_db));

		return FALSE;
	}

	return TRUE;
}

BOOL MySQL::InitBuffDB() {
	CHAR* errbuf = nullptr;

	const CHAR* sql = "CREATE TABLE IF NOT EXISTS Buff(Id INTEGER PRIMARY KEY, Name_KR TEXT NOT NULL);";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitBuffDB : %s", errbuf);
		sqlite3_free(errbuf);

		return FALSE;
	}
	std::string lang = Language.GetLanguageNameUsedForSQLite();
	std::string sql2 = "SELECT Name_" + lang + " From Buff Where Id = ?";
	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_buff_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 : %s", sqlite3_errmsg(_db));
		return FALSE;
	}
	return TRUE;
}

BOOL MySQL::InitSkillTimelineDB() {

	return TRUE;
}

BOOL MySQL::InitBuffTimelineDB() {

	return TRUE;
}

BOOL MySQL::Init() {

	BOOL success = TRUE;

	do {
		if (!InitDB()) {
			success = FALSE;
			break;
		}

		if (!InitSkillDB()) {
			success = FALSE;
			break;
		}

		if (!InitMonsterDB()) {
			success = FALSE;
			break;
		}

		if (!InitMapDB()) {
			success = FALSE;
			break;
		}

		if (!InitMemDB()) {
			success = FALSE;
			break;
		}

		if (!InitBuffDB()) {
			success = FALSE;
			break;
		}

		if (!InitSkillTimelineDB()) {
			success = FALSE;
			break;
		}

		if (!InitBuffTimelineDB()) {
			success = FALSE;
			break;
		}
	} while (FALSE);

	if (!success)
		FreeDB();

	return success;
}

BOOL MySQL::GetSkillName(UINT32 skillId, CHAR* out_buffer, SIZE_T out_buffer_length) {

	if (out_buffer == nullptr || _skill_stmt == nullptr)
		return FALSE;

	sprintf_s(out_buffer, out_buffer_length, "%d", skillId);

	sqlite3_reset(_skill_stmt);

	sqlite3_bind_int(_skill_stmt, 1, skillId);
	INT step;
	do {
		step = sqlite3_step(_skill_stmt);
	} while(step == SQLITE_BUSY || step == SQLITE_LOCKED);
	if (step == SQLITE_DONE)
	{
		strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
		out_buffer[out_buffer_length - 1] = 0x00;
		return FALSE;
	}
	if (step == SQLITE_ROW) {
		const CHAR* result = (const CHAR*)sqlite3_column_text(_skill_stmt, 0);

		if (result == nullptr)
		{
			strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return FALSE;
		}
		if (strlen(result) > out_buffer_length)
		{
			strncpy(out_buffer, result, out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return FALSE;
		}

		strcpy_s(out_buffer, out_buffer_length, result);
	}
	
	return TRUE;
}

BOOL MySQL::GetMonsterName(UINT32 DB2, CHAR* out_buffer, SIZE_T out_buffer_length) {

	if (out_buffer == nullptr || _monster_stmt == nullptr)
		return FALSE;

	//if (DB1 == 0) {
	//	strcpy_s(out_buffer, out_buffer_length, const_cast<CHAR*>(u8"메이즈 정보 X"));
	//	return TRUE;
	//}

	sprintf_s(out_buffer, out_buffer_length, "%u", DB2);

	sqlite3_reset(_monster_stmt);

	sqlite3_bind_int(_monster_stmt, 1, DB2);
	INT step;
	do {
		step = sqlite3_step(_monster_stmt);
	} while(step == SQLITE_BUSY || step == SQLITE_LOCKED);
	if (step == SQLITE_ROW) {
		const CHAR* result = (const CHAR*)sqlite3_column_text(_monster_stmt, 0);

		if (result == nullptr)
		{
			//strncpy(out_buffer,"FailToGetName",out_buffer_length-2);
			sprintf_s(out_buffer,out_buffer_length-2,"FailToGetName(%u)",DB2);
			out_buffer[out_buffer_length-1] = 0x00;
			return FALSE;
		}
		if (strlen(result) > out_buffer_length)
		{
			strncpy(out_buffer,result,out_buffer_length-2);
			out_buffer[out_buffer_length-1] = 0x00;
			return FALSE;
		}
		strcpy_s(out_buffer, out_buffer_length, result);
	}
	else
	{
		sprintf_s(out_buffer, out_buffer_length - 2, "FailToGetName(%u)", DB2);
		out_buffer[out_buffer_length - 1] = 0x00;
		return FALSE;
	}
	return TRUE;
}

BOOL MySQL::GetMapName(UINT32 mapID, CHAR* out_buffer, SIZE_T out_buffer_length){

	if (out_buffer == nullptr || _map_stmt == nullptr)
		return FALSE;

	if (mapID == 0) {
		strcpy_s(out_buffer, out_buffer_length, Language.GetText(STR_WORLD_NO_INFORMATION).c_str());
		return TRUE;
	}
	sprintf_s(out_buffer, out_buffer_length, "%d", mapID);

	sqlite3_reset(_map_stmt);

	sqlite3_bind_int(_map_stmt, 1, mapID);

	INT step;
	do {
		step = sqlite3_step(_map_stmt);
	} while (step == SQLITE_BUSY || step == SQLITE_LOCKED);
	if (step == SQLITE_ROW) {
		const CHAR* result = (const CHAR*)sqlite3_column_text(_map_stmt, 0);

		if (result == nullptr)
		{
			strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return FALSE;
		}
		if (strlen(result) > out_buffer_length)
		{
			strncpy(out_buffer, result, out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return FALSE;
		}

		strcpy_s(out_buffer, out_buffer_length, result);
	}
	else
	{
		strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
		out_buffer[out_buffer_length - 1] = 0x00;
		return FALSE;
	}
	return TRUE;
}

BOOL MySQL::GetBuffName(UINT32 buffId, CHAR* out_buffer, SIZE_T out_buffer_length) {

	if (out_buffer == nullptr || _buff_stmt == nullptr)
		return FALSE;

	if (buffId == 0) {
		strcpy_s(out_buffer, out_buffer_length, const_cast<CHAR*>(u8"Unknown"));
		return TRUE;
	}

	sprintf_s(out_buffer, out_buffer_length, "%d", buffId);

	sqlite3_reset(_buff_stmt);

	sqlite3_bind_int(_buff_stmt, 1, buffId);

	INT step;
	do {
		step = sqlite3_step(_buff_stmt);
	} while (step == SQLITE_BUSY || step == SQLITE_LOCKED);
	if (step == SQLITE_ROW) {
		const CHAR* result = (const CHAR*)sqlite3_column_text(_buff_stmt, 0);

		if (result == nullptr)
		{
			strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return FALSE;
		}
		if (strlen(result) > out_buffer_length)
		{
			strncpy(out_buffer, result, out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return FALSE;
		}

		strcpy_s(out_buffer, out_buffer_length, result);
	}
	else
	{
		strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
		out_buffer[out_buffer_length - 1] = 0x00;
		return FALSE;
	}
	return TRUE;
}
std::map<unsigned int,std::string> stats =
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
std::string MySQL::GetStatName(unsigned int statid)
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

