#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETMONSTERKILLED {
	uint32_t _killedId;
	//uint8_t _unknown01[4];//3
}SWPACKETMONSTERKILLED;
#pragma pack(pop)

class SWPacketMonsterKilled : public SWPacket {

protected:
	SWPacketMonsterKilled() {}

public:
	SWPacketMonsterKilled(SWHEADER* swheader, uint8_t* data);
	~SWPacketMonsterKilled() {}

	void Do();
	void Debug();
	void Log();
};