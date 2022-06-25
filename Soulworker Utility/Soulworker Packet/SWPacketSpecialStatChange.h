#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSPECIALSTATCHANGE_HEADER {
	UINT32 _playerID;
	BYTE _statsCount;
}SWPACKETSPECIALSTATCHANGE_HEADER;


typedef struct _SWPACKETSPECIALSTATCHANGE_DATA {
	USHORT _statType;
	FLOAT _statValue;
}SWPACKETSPECIALSTATCHANGE_DATA;

#pragma pack(pop)

class SWPacketSpecialStatChange : public SWPacket {

protected:
	SWPacketSpecialStatChange() {}

public:
	SWPacketSpecialStatChange(SWHEADER* swheader, BYTE* data);
	~SWPacketSpecialStatChange() {}

	VOID Do();
	VOID Debug();
	VOID Log();
};