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

	bool InitDB();
	bool InitMemDB();
	void FreeDB();

	bool InitSkillDB();
	bool InitMonsterDB();
	bool InitMapDB();
	bool InitBuffDB();
	bool InitSkillTimelineDB();
	bool InitBuffTimelineDB();

	sqlite3_stmt* _skill_stmt;
	sqlite3_stmt* _monster_stmt;
	sqlite3_stmt* _map_stmt;
	sqlite3_stmt* _map_stmt_eng;
	sqlite3_stmt* _buff_stmt;

public:
	MySQL();
	~MySQL();

	bool Init();
	bool GetSkillName(uint32_t skillId, _Out_ char* out_buffer, _In_ size_t out_buffer_length);
	bool GetMonsterName(uint32_t DB2, _Out_ char* out_buffer, _In_ size_t out_buffer_length);
	bool GetMonsterType(uint32_t DB2, int32_t* type);
	bool GetMapName(uint32_t mapId, _Out_ char* out_buffer, _In_ size_t out_buffer_length);
	bool GetMapNameENG(uint32_t mapId, _Out_ char* out_buffer, _In_ size_t out_buffer_length);
	bool GetBuffName(uint32_t buffId, _Out_ char* out_buffer, _In_ size_t out_buffer_length, _Out_ char* out_buffer_desc = NULL, _In_ size_t out_buffer_desc_length = NULL);
};