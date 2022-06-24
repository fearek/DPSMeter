#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETSPECIALSTATCHANGE_HEADER {
	UINT32 _playerID;
	BYTE _statsCount;
}SWPACKETSPECIALSTATCHANGE_HEADER;

#if defined(SERVER_KOREA)
typedef struct _SWPACKETSPECIALSTATCHANGE_DATA {
	FLOAT _statValue;
	USHORT _statType;
	BYTE _unknown01[8];
}SWPACKETSPECIALSTATCHANGE_DATA;
#endif

#if defined(SERVER_STEAM)
typedef struct _SWPACKETSPECIALSTATCHANGE_DATA {
	USHORT _statType;
	FLOAT _statValue;
	BYTE _unknown01[8];
}SWPACKETSPECIALSTATCHANGE_DATA;
#endif
#if defined(SERVER_JAPAN) // same as KR server
typedef struct _SWPACKETSPECIALSTATCHANGE_DATA {
	FLOAT _statValue;
	USHORT _statType;
	BYTE _unknown01[8];
}SWPACKETSPECIALSTATCHANGE_DATA;
#endif

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