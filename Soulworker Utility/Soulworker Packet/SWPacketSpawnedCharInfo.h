#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSPAWNEDcharINFO_HEADER {
	uint32_t _playerId;
	uint16_t _nameSize;
}SWPACKETSPAWNEDcharINFO_HEADER;

#pragma pack(pop)

class SWPacketSpawnedCharInfo : public SWPacket {
protected:
	SWPacketSpawnedCharInfo() {}

public:
	SWPacketSpawnedCharInfo(SWHEADER* swheader, uint8_t* data);
	~SWPacketSpawnedCharInfo() {}

	void Do();
	void Log();
	void Debug();
};