#pragma once
#include ".\Language\Region.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)

typedef struct _SWPACKET_PING {
	UINT32 _ping;
	
}SWPACKET_PING;

#pragma pack(pop)
class SWCPing : public SWPacket {
protected:
	SWHEADER* _swheader;
	BYTE* _data;

	SWCPing() {}
	SWCPing(SWPacket& other) {}

public:
	SWCPing(SWHEADER* swheader, BYTE* data);
	virtual ~SWCPing() {}

	virtual VOID Debug();
	virtual VOID Log();
	virtual VOID Do();
};