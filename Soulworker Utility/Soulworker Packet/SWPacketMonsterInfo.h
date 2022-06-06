#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETMONSTERINFO {
	BYTE _unknown01;
	UINT32 _id;
	BYTE _unknown02[41];
#ifdef SERVER_KOREA
	BYTE _unknown02[17];
#endif
#ifdef SERVER_STEAM
	BYTE _unknown02[17]; // unknown01 -> id -> unknown02 ????? 33
#endif
#ifdef SERVER_JAPAN
	BYTE _unknown02[17]; // same as KR server
#endif
	UINT32 _realDB2;
	UINT32 _owner_id;
	BYTE _unknown03[142];
}SWPACKETMONSTERINFO;

#pragma pack(pop)

class SWPacketMonsterInfo : public SWPacket {
protected:
	SWPacketMonsterInfo() {}

public:
	SWPacketMonsterInfo(SWHEADER* swheader, BYTE* data);
	~SWPacketMonsterInfo() {}

	VOID Do();
	VOID Log();
	VOID Debug();
};