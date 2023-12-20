#pragma once

#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)

typedef struct _SWPACKET_MYSKILLUSED {
	uint32_t _skillId;
	uint32_t _playerId;
	float _locationX;
	float _locationY;
	float _locationZ;
	float _direction;
	uint8_t _unknown01[30];
}SWPACKET_MYSKILLUSED;

#pragma pack(pop)


class SWSPacketMySkillUsed : public SWPacket {
protected:
	SWHEADER* _swheader;
	uint8_t* _data;

	SWSPacketMySkillUsed() {}
	SWSPacketMySkillUsed(SWPacket& other) {}

public:
	SWSPacketMySkillUsed(SWHEADER* swheader, uint8_t* data);
	virtual ~SWSPacketMySkillUsed() {}

	virtual void Debug();
	virtual void Log();
	virtual void Do();
};