#pragma once
#include ".\Language\Region.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)

typedef struct _SWPACKET_PRESENCE {
	UINT32 maze;
	UINT8 playerclass;
	UINT16 nicklength;

}SWPACKET_PRESENCE;

#pragma pack(pop)
class SWCPresence : public SWPacket {
protected:
	SWHEADER* _swheader;
	BYTE* _data;

	SWCPresence() {}
	SWCPresence(SWPacket& other) {}

public:
	SWCPresence(SWHEADER* swheader, BYTE* data);
	virtual ~SWCPresence() {}

	virtual VOID Debug();
	virtual VOID Log();
	virtual VOID Do();
};