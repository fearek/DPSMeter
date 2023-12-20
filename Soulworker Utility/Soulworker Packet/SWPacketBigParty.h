#pragma once

#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#define SWPACKETBIGPARTY_DUMMY 46 //2304

#pragma pack(push, 1)

typedef struct _SWPACKETBIGPARTY_HEADER {
	uint8_t _unknown01[4];
	uint32_t _posHostID;
	uint8_t _unknown02[10];
	uint8_t _posPlayerCount;
}SWPACKETBIGPARTY_HEADER;

typedef struct _SWPACKETBIGPARTY_DATA {
	uint32_t _playerID;
	uint16_t _nickSize;
}SWPACKETBIGPARTY_DATA;

#pragma pack(pop)

class SWPacketBigParty : public SWPacket {
protected:
	SWPacketBigParty() {}

public:
	SWPacketBigParty(SWHEADER* swheader, uint8_t* data);
	~SWPacketBigParty() {}

	void Do();
	void Log();
	void Debug();
};