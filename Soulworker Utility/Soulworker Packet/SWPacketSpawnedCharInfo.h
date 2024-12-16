#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSPAWNEDcharINFO_HEADER {
	uint32_t _playerId;
	unsigned short _nameSize;
}SWPACKETSPAWNEDcharINFO_HEADER;

#pragma pack(pop)

class SWPacketSpawnedcharInfo : public SWPacket {
protected:
	SWPacketSpawnedcharInfo() {}

public:
	SWPacketSpawnedcharInfo(SWHEADER* swheader, BYTE* data);
	~SWPacketSpawnedcharInfo() {}

	void Do();
	void Log();
	void Debug();
};