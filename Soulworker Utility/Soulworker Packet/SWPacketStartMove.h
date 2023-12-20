#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSTARTMOVE {
	uint32_t _playerId;
	uint8_t _unknown01[4];
	uint16_t _mapId;
	uint8_t _unknown02[2];
	float _locationX;
	float _locationY;
	float _locationZ;
	float _direction;
	float _endLocationX;
	float _endLocationY;
	uint8_t _screen[4];
	uint8_t _unknown04;
	float _speed;
	uint8_t _unknown05[6];
}SWPACKETSTARTMOVE;

#pragma pack(pop)

class SWPacketStartMove : public SWPacket {
protected:
	SWPacketStartMove() {}

public:
	SWPacketStartMove(SWHEADER* swheader, uint8_t* data);
	~SWPacketStartMove() {}

	void Do();
	void Log();
	void Debug();
};