#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETBUFFOUT {
	uint32_t _playerID;
	uint16_t _buffID;
	uint8_t _unknwon01;
	uint32_t _giverID;
}SWPACKETBUFFOUT;
#pragma pack(pop)

class SWPacketBuffOut : public SWPacket {
protected:
	SWPacketBuffOut() {}

public:
	SWPacketBuffOut(SWHEADER* swheader, uint8_t* data);
	~SWPacketBuffOut() {}

	void Do();
	void Log();
	void Debug();
};