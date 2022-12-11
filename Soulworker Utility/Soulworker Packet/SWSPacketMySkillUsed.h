#pragma once

#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)

typedef struct _SWPACKET_MYSKILLUSED {
	UINT32 _skillId;
	UINT32 _playerId;
	FLOAT _locationX;
	FLOAT _locationY;
	FLOAT _locationZ;
	FLOAT _direction;
	BYTE _unknown01[30];
}SWPACKET_MYSKILLUSED;

#pragma pack(pop)


class SWSPacketMySkillUsed : public SWPacket {
protected:
	SWHEADER* _swheader;
	BYTE* _data;

	SWSPacketMySkillUsed() {}
	SWSPacketMySkillUsed(SWPacket& other) {}

public:
	SWSPacketMySkillUsed(SWHEADER* swheader, BYTE* data);
	virtual ~SWSPacketMySkillUsed() {}

	virtual VOID Debug();
	virtual VOID Log();
	virtual VOID Do();
};