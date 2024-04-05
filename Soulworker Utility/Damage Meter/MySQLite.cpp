#include "pch.h"

#include ".\Damage Meter\MySQLite.h"

MySQL::MySQL() : _db(nullptr), _memdb(nullptr) {

}

MySQL::~MySQL() {
	FreeDB();
}

bool MySQL::InitDB(){

	if (sqlite3_open(SWDBPATH, &_db) != SQLITE_OK) {
		LogInstance.WriteLog(const_cast<char*>("Error in InitDB : %s"), sqlite3_errmsg(_db));
		sqlite3_close(_db);
		_db = nullptr;

		return false;
	}

	return true;
}

bool MySQL::InitMemDB() {

	if (sqlite3_open(":memory:", &_memdb) != SQLITE_OK) {
		LogInstance.WriteLog(const_cast<char*>("Error in InitMemDB : %s"), sqlite3_errmsg(_memdb));
		sqlite3_close(_memdb);
		_memdb = nullptr;

		return false;
	}

	return true;
}

void MySQL::FreeDB() {

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

bool MySQL::InitSkillDB() {

	char* errbuf = nullptr;

	const char* sql = "CREATE TABLE IF NOT EXISTS Skill(Id intEGER PRIMARY KEY, Name_EN TEXT, Name_TC TEXT, Name_JP TEXT, Name_KR TEXT);";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog(const_cast<char*>("Error in InitSkillDB : %s"), errbuf);
		sqlite3_free(errbuf);

		return false;
	}

//	const char* sql2 = "SELECT Name From Skill Where Id = ?";
	std::string sql2 = std::string("SELECT Name_") + std::string(LANGMANAGER.GetText("STR_SQL_SUFFIX")) + " From Skill Where Id = ?";

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_skill_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog(const_cast<char*>("Error in sqlite3_prepare_v2 : %s"), sqlite3_errmsg(_db));

		return false;
	}

	return true;
}

bool MySQL::InitMonsterDB() {

	char* errbuf = nullptr;

	//const char* sql = "CREATE TABLE IF NOT EXISTS Monster(Db1 intEGER, Db2 intEGER, Name_KR TEXT NOT NULL, PRIMARY KEY(Db1, Db2));";
	const char* sql = "CREATE TABLE IF NOT EXISTS Monster(Id intEGER PRIMARY KEY, Name_EN TEXT, Name_TC TEXT, Name_JP TEXT, Name_KR TEXT);";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitMonsterDB : %s", errbuf);
		sqlite3_free(errbuf);

		return false;
	}

	//std::string sql2 = "SELECT Name_" LANG " From Monster Where Db1 = ? and Db2 = ?";
	std::string sql2 = "SELECT Name_" + std::string(LANGMANAGER.GetText("STR_SQL_SUFFIX")) + ", type From Monster Where Id = ?";

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_monster_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 : %s", sqlite3_errmsg(_db));

		return false;
	}

	return true;
}

bool MySQL::InitMapDB() {
	char* errbuf = nullptr;

	const char* sql = "CREATE TABLE IF NOT EXISTS Map(Id intEGER PRIMARY KEY, Name_EN TEXT, Name_TC TEXT, Name_JP TEXT, Name_KR TEXT);";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog("Error in InitMapDB : %s", errbuf);
		sqlite3_free(errbuf);

		return false;
	}
	std::string sql2 = "SELECT Name_" + std::string(LANGMANAGER.GetText("STR_SQL_SUFFIX")) + " From Map Where Id = ?";

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_map_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 MAP : %s", sqlite3_errmsg(_db));

		return false;
	}
	std::string sql3 = "SELECT Name_EN From Map Where Id = ?";
	if (sqlite3_prepare_v2(_db, sql3.c_str(), -1, &_map_stmt_eng, 0) != SQLITE_OK) {
		LogInstance.WriteLog("Error in sqlite3_prepare_v2 MAP2 : %s", sqlite3_errmsg(_db));

		return false;
	}
	return true;
}

bool MySQL::InitBuffDB() {
	char* errbuf = nullptr;

	const char* sql = "CREATE TABLE IF NOT EXISTS Buff (Id intEGER PRIMARY KEY, Name_EN TEXT, Name_TC TEXT, Name_JP TEXT, Name_KR TEXT, Desc_EN TEXT, Desc_TC TEXT, Desc_JP TEXT, Desc_KR TEXT)";

	if (sqlite3_exec(_db, sql, 0, 0, &errbuf) != SQLITE_OK) {
		LogInstance.WriteLog(const_cast<char*>("Error in InitBuffDB : %s"), errbuf);
		sqlite3_free(errbuf);

		return false;
	}

	std::string sql2 = "SELECT Name_" + std::string(LANGMANAGER.GetText("STR_SQL_SUFFIX")) + ",Desc_" + std::string(LANGMANAGER.GetText("STR_SQL_SUFFIX")) + " From Buff Where Id = ?";

	if (sqlite3_prepare_v2(_db, sql2.c_str(), -1, &_buff_stmt, 0) != SQLITE_OK) {
		LogInstance.WriteLog(const_cast<char*>("Error in sqlite3_prepare_v2 : %s"), sqlite3_errmsg(_db));

		return false;
	}

	return true;
}

bool MySQL::InitSkillTimelineDB() {

	return true;
}

bool MySQL::InitBuffTimelineDB() {

	return true;
}
bool MySQL::GetMapNameENG(uint32_t mapID, char* out_buffer, size_t out_buffer_length) {

	if (out_buffer == nullptr || _map_stmt_eng == nullptr)
		return false;

	if (mapID == 0) {
		strcpy_s(out_buffer, out_buffer_length, "No info");
		return true;
	}
	sprintf_s(out_buffer, out_buffer_length, "%u", mapID);

	sqlite3_reset(_map_stmt_eng);

	sqlite3_bind_int(_map_stmt_eng, 1, mapID);

	int step;
	do {
		step = sqlite3_step(_map_stmt_eng);
	} while (step == SQLITE_BUSY || step == SQLITE_LOCKED);
	if (step == SQLITE_ROW) {
		const char* result = (const char*)sqlite3_column_text(_map_stmt_eng, 0);

		if (result == nullptr)
		{
			strncpy(out_buffer, "FailToGetName", out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return false;
		}
		if (strcmp(result, "UNKNOWN") == 0)
		{
			return false;
		}
		if (strlen(result) > out_buffer_length)
		{
			strncpy(out_buffer, result, out_buffer_length - 2);
			out_buffer[out_buffer_length - 1] = 0x00;
			return false;
		}
		strcpy_s(out_buffer, out_buffer_length, result);
	}
	else
	{
		return false;
	}
	return true;
}
bool MySQL::Init() {

	bool success = true;

	do {
		if (!InitDB()) {
			success = false;
			break;
		}

		if (!InitSkillDB()) {
			success = false;
			break;
		}

		if (!InitMonsterDB()) {
			success = false;
			break;
		}

		if (!InitMapDB()) {
			success = false;
			break;
		}

		if (!InitMemDB()) {
			success = false;
			break;
		}

		if (!InitBuffDB()) {
			success = false;
			break;
		}

		if (!InitSkillTimelineDB()) {
			success = false;
			break;
		}

		if (!InitBuffTimelineDB()) {
			success = false;
			break;
		}
	} while (false);

	if (!success)
		FreeDB();

	return success;
}

bool MySQL::GetSkillName(uint32_t skillId, char* out_buffer, size_t out_buffer_length) {

	if (out_buffer == nullptr || _skill_stmt == nullptr)
		return false;

	sprintf_s(out_buffer, out_buffer_length, "%d", skillId);

	sqlite3_reset(_skill_stmt);

	sqlite3_bind_int(_skill_stmt, 1, skillId);
	int step = sqlite3_step(_skill_stmt);

	if (step == SQLITE_ROW) {
		const char* result = (const char*)sqlite3_column_text(_skill_stmt, 0);

		if (result == nullptr || strlen(result) > out_buffer_length)
			return false;

		strcpy_s(out_buffer, out_buffer_length, result);
	}

	return true;
}

bool MySQL::GetMonsterName(uint32_t DB2, char* out_buffer, size_t out_buffer_length) {

	if (out_buffer == nullptr || _monster_stmt == nullptr)
		return false;

	sprintf_s(out_buffer, out_buffer_length, "%d", DB2);

	sqlite3_reset(_monster_stmt);

	sqlite3_bind_int(_monster_stmt, 1, DB2);

	int step = sqlite3_step(_monster_stmt);

	if (step == SQLITE_ROW) {
		const char* result = (const char*)sqlite3_column_text(_monster_stmt, 0);

		if (result == nullptr || strlen(result) > out_buffer_length)
			return false;

		strcpy_s(out_buffer, out_buffer_length, result);
	}

	return true;
}

bool MySQL::GetMonsterType(uint32_t DB2, int32_t* type) {

	if (type == nullptr || _monster_stmt == nullptr)
		return false;

	sqlite3_reset(_monster_stmt);

	sqlite3_bind_int(_monster_stmt, 1, DB2);

	int step = sqlite3_step(_monster_stmt);

	if (step == SQLITE_ROW) {
		int32_t result = sqlite3_column_int(_monster_stmt, 1);
		memcpy_s(type, sizeof(int32_t), &result, sizeof(int32_t));
	}

	return true;
}

bool MySQL::GetMapName(uint32_t mapID, char* out_buffer, size_t out_buffer_length){

	if (out_buffer == nullptr || _map_stmt == nullptr)
		return false;

	if (mapID == 0) {
		strcpy_s(out_buffer, out_buffer_length, LANGMANAGER.GetText("STR_WORLD_NO_INFORMATION").data());
		return true;
	}

	sprintf_s(out_buffer, out_buffer_length, "%d", mapID);

	sqlite3_reset(_map_stmt);

	sqlite3_bind_int(_map_stmt, 1, mapID);

	int step = sqlite3_step(_map_stmt);

	if (step == SQLITE_ROW) {
		const char* result = (const char*)sqlite3_column_text(_map_stmt, 0);

		if (result == nullptr || strlen(result) > out_buffer_length)
			return false;

		strcpy_s(out_buffer, out_buffer_length, result);
	}

	return true;
}

bool MySQL::GetBuffName(uint32_t buffId, char* out_buffer, size_t out_buffer_length, char* out_buffer_desc, size_t out_buffer_desc_length) {

	if (out_buffer == nullptr || _buff_stmt == nullptr)
		return false;

	if (buffId == 0) {
		strcpy_s(out_buffer, out_buffer_length,u8"Unknown");
		return true;
	}

	sprintf_s(out_buffer, out_buffer_length, "%d", buffId);

	sqlite3_reset(_buff_stmt);

	sqlite3_bind_int(_buff_stmt, 1, buffId);

	int step = sqlite3_step(_buff_stmt);

	if (step == SQLITE_ROW) {
		const char* result = (const char*)sqlite3_column_text(_buff_stmt, 0);

		if (result == nullptr || strlen(result) > out_buffer_length)
			return false;

		strcpy_s(out_buffer, out_buffer_length, result);

		if (out_buffer_desc != NULL)
		{
			result = (const char*)sqlite3_column_text(_buff_stmt, 1);

			if (result == nullptr || strlen(result) > out_buffer_desc_length)
				return false;

			strcpy_s(out_buffer_desc, out_buffer_desc_length, result);
		}
	}

	return true;
}