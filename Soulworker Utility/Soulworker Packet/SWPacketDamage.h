#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include <unordered_set>

#pragma pack(push, 1)

typedef struct _SWPACKETDAMAGE_MONSTER {
	UINT32 _monsterID; // 4
	BYTE _unknown01; // 5
	BYTE _damageType; // 6
	UINT32 _totalDMG; // 10
	UINT32 _soulstoneDMG; // 14
	UINT32 _remainHP; // 18
	FLOAT _unknownF1; // 22
	FLOAT _unknownF2; // 26
	FLOAT _unknownF3; // 30
#ifdef SERVER_KOREA
	BYTE _unknown02[22]; // sum 52 // previous value 18
#endif
#ifdef SERVER_STEAM
	BYTE _unknown02[22]; //previous value 22 glb 10
#endif
#ifdef SERVER_JAPAN
    BYTE _unknown02[18]; // same as past of KR server
#endif
}SWPACKETDAMAGE_MONSTER;

typedef struct _SWPACKETDAMAGE_PLAYER {
	UINT32 _playerID; // 4
	BYTE _unknown01[20]; // 24
	UINT32 _skillID; // 28
	BYTE _unknown02[2]; // 30
	USHORT _maxCombo; // 32
	BYTE _unknown03[2]; // 34
}SWPACKETDAMAGE_PLAYER;
	
#pragma pack(pop)
static std::unordered_set<UINT32> pauseIdList({
	31309102, // 루나폴 - 에드가
	31301001, // 바썬 - 플레마 1페
	31301002, // 바썬 - 플레마 2페
	31310101 // 브세노말 - 테네브리스 1페
	// 702 // 일시정지 테스트용 트센몹
	});
static std::unordered_set<UINT32> endIdList({
	31308001, // 히하 - 라파쿰바
	31309151, // 루나폴 - 정크 퀸
	31301003, // 바썬 - 플레마 3페
	31310102 // 브세노말 - 테네브리스 2페
	});

class SWPacketDamage : public SWPacket {
private:
	VOID AttackOfMonster();

protected:
	SWPacketDamage() {}

public:
	SWPacketDamage(SWHEADER* swheader, BYTE* data);
	~SWPacketDamage() {}

	VOID Do();
	VOID Debug();
	VOID Log() {};
};