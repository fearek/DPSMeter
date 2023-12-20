#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETBUFFIN {
	uint32_t _playerID;
	uint16_t _buffID;
	float _duration;
	uint8_t _stack;
	uint32_t _giverID;
	uint8_t _unknown02;
}SWPACKETBUFFIN;
#pragma pack(pop)

class SWPacketBuffIn : public SWPacket {
protected:
	SWPacketBuffIn() {}

public:
	SWPacketBuffIn(SWHEADER* swheader, uint8_t* data);
	~SWPacketBuffIn() {}

	void Do();
	void Log();
	void Debug();
};