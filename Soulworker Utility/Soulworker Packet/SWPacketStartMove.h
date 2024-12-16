#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSTARTMOVE {
	uint32_t _playerId;
	BYTE _unknown01[4];
	unsigned short _mapId;
	BYTE _unknown02[2];
	float _locationX;
	float _locationY;
	float _locationZ;
	float _direction;
	float _endLocationX;
	float _endLocationY;
	BYTE _screen[4];
	BYTE _unknown04;
	float _speed;
	BYTE _unknown05[6];
}SWPACKETSTARTMOVE;

#pragma pack(pop)

class SWPacketStartMove : public SWPacket {
protected:
	SWPacketStartMove() {}

public:
	SWPacketStartMove(SWHEADER* swheader, BYTE* data);
	~SWPacketStartMove() {}

	void Do();
	void Log();
	void Debug();
};