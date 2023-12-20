#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETHEARTBEAT {
	uint8_t _unknown01; //0430new
	uint32_t _tick; // tick
	uint8_t _unknown02[4];
}SWPACKETHEARTBEAT;

#pragma pack(pop)

class SWPacketHeartbeat : public SWPacket {
protected:
	SWPacketHeartbeat() {}

	int64_t _ts;

public:
	SWPacketHeartbeat(SWHEADER* swheader, uint8_t* data);
	~SWPacketHeartbeat() {}

	void Do();
	void Log();
	void Debug();
};