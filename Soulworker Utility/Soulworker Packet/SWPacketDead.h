#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKET_DEAD {
	uint32_t _playerid;
	uint8_t _unknown2[7];
}SWPACKET_DEAD;

#pragma pack(pop)

class SWPacketDead : public SWPacket {

protected:
	SWPacketDead() {}

public:
	SWPacketDead(SWHEADER* swheader, uint8_t* data);
	~SWPacketDead() {}

	void Do();
	void Debug();
	void Log();
};