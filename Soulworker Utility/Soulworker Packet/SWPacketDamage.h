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
	702, // Trainning Master

	/* LF */
	31309102, // Azure Force. Edgar

	/* VS */
	31301001, // Flemma P1
	31301002, // Flemma P2

	/* VS Solo */
	33301001, // Flemma P1
	33301002, // Flemma P2

	/* BS */
	31310101, // Tenebris P1
	31310103, // BS Hard Phase 1

	/* BS Solo */
	32320101, // Tenebris P1
	});
static std::unordered_set<UINT32> endIdList({
	/* HH */
	31308001, // Raphakumba

	/* LF */
	31309151, // Junk Queen

	/* VS */
	31301003, // Flemma P3

	/* VS Solo */
	33301003, // Flemma P3

	/* BS */
	31310102, // Tenebris P2
	31310107, // Tenebris Hard P2

	/* BS Solo */
	32320102, // Tenebris P2

	/* RANK */
	32308101, // Raphakumba Rank
	32301001, // Flemma Rank
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