#pragma once

#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

#pragma pack(pop)

class SWPacketSquad : public SWPacket {
protected:
	SWPacketSquad() {}

public:
	SWPacketSquad(SWHEADER* swheader, uint8_t* data);
	~SWPacketSquad() {}

	void Do();
	void Log();
	void Debug();
};