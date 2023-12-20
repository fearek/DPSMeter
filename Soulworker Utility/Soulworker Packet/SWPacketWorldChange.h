#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETWORLDCHANGE {
	uint32_t _id;
	uint8_t _unknwon1[20];
	uint16_t _worldID;
	uint8_t _unknwon2[10];
	uint16_t _serverIPLen;
	uint8_t _serverIP;
}SWPACKETWORLDCHANGE;

#pragma pack(pop)

class SWPacketWorldChange : public SWPacket {
protected:
	SWPacketWorldChange() {}

public:
	SWPacketWorldChange(SWHEADER* swheader, uint8_t* data);
	~SWPacketWorldChange() {}

	void Do();
	void Log();
	void Debug();
};