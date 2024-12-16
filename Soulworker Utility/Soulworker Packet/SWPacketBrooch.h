#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETBROOCH {
	uint32_t _playerID;
	uint16_t _broochID;
}SWPACKETBROOCH;
#pragma pack(pop)

class SWPacketBrooches : public SWPacket {
protected:
	SWPacketBrooches() {}

public:
	SWPacketBrooches(SWHEADER* swheader, BYTE* data);
	~SWPacketBrooches() {}

	void Do();
	void Log();
	void Debug();
};