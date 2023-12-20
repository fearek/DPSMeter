#pragma once

#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#define SWPACKETPARTY_DUMMY 46 //0512

#pragma pack(push, 1)

typedef struct _SWPACKETPARTY_HEADER {
	uint8_t _unknown01[4]; //0430new
	uint32_t _partyHostID;
	uint8_t _unknown02[10];
	uint8_t _partyPlayerCount;
}SWPACKETPARTY_HEADER;

typedef struct _SWPACKETPARTY_DATA {
	uint32_t _playerID;
	uint16_t _nickSize;
}SWPACKETPARTY_DATA;

#pragma pack(pop)

class SWPacketParty : public SWPacket {
protected:
	SWPacketParty() {}

public:
	SWPacketParty(SWHEADER* swheader, uint8_t* data);
	~SWPacketParty() {}

	void Do();
	void Log();
	void Debug();
};