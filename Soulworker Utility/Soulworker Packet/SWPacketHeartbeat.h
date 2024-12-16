#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETHEARTBEAT {
	BYTE _unknown01; //0430new
	uint32_t _tick; // tick
	BYTE _unknown02[4];
}SWPACKETHEARTBEAT;

#pragma pack(pop)

class SWPacketHeartbeat : public SWPacket {
protected:
	SWPacketHeartbeat() {}

	int64_t _ts;

public:
	SWPacketHeartbeat(SWHEADER* swheader, BYTE* data, uint64_t ts);
	~SWPacketHeartbeat() {}

	void Do();
	void Log();
	void Debug();
};