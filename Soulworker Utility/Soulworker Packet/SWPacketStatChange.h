#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSTATCHANGE_HEADER {
	uint8_t _unknown01;
	uint32_t _playerID;
	uint8_t _statsCount;
}SWPACKETSTATCHANGE_HEADER;

typedef struct _SWPACKETSTATCHANGE_DATA {
	float _statValue;
	uint16_t _statType;
	uint8_t _unknown01[8]; //0430new
}SWPACKETSTATCHANGE_DATA;

#pragma pack(pop)

class SWPacketStatChange : public SWPacket {

protected:
	SWPacketStatChange() {}

public:
	SWPacketStatChange(SWHEADER* swheader, uint8_t* data);
	~SWPacketStatChange() {}

	void Do();
	void Debug();
	void Log();
};