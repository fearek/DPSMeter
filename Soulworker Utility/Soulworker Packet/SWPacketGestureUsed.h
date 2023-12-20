#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETGESTUREUSED {
	uint32_t _playerID;
	uint32_t _gestureId;
	float _locationX;
	float _locationY;
	float _locationZ;
	float _direction;
	float _screen;
}SWPACKETGESTUREUSED;
#pragma pack(pop)

class SWPacketGestureUsed : public SWPacket {

protected:
	SWPacketGestureUsed() {}

public:
	SWPacketGestureUsed(SWHEADER* swheader, uint8_t* data);
	~SWPacketGestureUsed() {}

	void Do();
	void Debug();
	void Log();
};