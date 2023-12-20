#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Damage Meter\MonsterList.h"

#pragma pack(push, 1)

typedef struct _SWPACKETDAMAGE_MONSTER {
	uint32_t _monsterID; // 4
	uint8_t _unknown01; // 1
	uint8_t _damageType; //1
	uint32_t _totalDMG; //4
	uint32_t _soulstoneDMG; // 4
	uint32_t _remainHP; //4
	float _unknownF1; // 4
	float _unknownF2; // 4
	float _unknownF3; // 4
	uint8_t _unknown02[22]; // 0605
}SWPACKETDAMAGE_MONSTER;

typedef struct _SWPACKETDAMAGE_PLAYER {
	uint32_t _playerID;
	uint8_t _unknown01[20]; //0403new
	uint32_t _skillID; 
	uint8_t _unknown02[2]; //0403new
	uint16_t _maxCombo;
	uint8_t _unknown03[2]; //0403new
}SWPACKETDAMAGE_PLAYER;
	
#pragma pack(pop)

class SWPacketDamage : public SWPacket {
private:
	void AttackOfMonster();

protected:
	SWPacketDamage() {}

public:
	SWPacketDamage(SWHEADER* swheader, uint8_t* data);
	~SWPacketDamage() {}

	void Do();
	void Debug();
	void Log() {};
};