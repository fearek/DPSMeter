#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPACKETCOOLDOWN {
	UINT32 _playerID;
	FLOAT _value;
	BYTE _unknown01[5];
}SWPACKETCOOLDOWN;
#pragma pack(pop)

class SWPacketCooldown : public SWPacket {
protected:
	SWPacketCooldown() {}

public:
	SWPacketCooldown(SWHEADER* swheader, BYTE* data);
	~SWPacketCooldown() {}

	VOID Do();
	VOID Log();
	VOID Debug();
};