#pragma once

#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWSPACKET_HEARTBEAT {
	BYTE unk01;
	uint32_t _tick;
}_SWSPACKET_HEARTBEAT;

#pragma pack(pop)


class SWSPacketHeartbeat : public SWPacket {
protected:
	int64_t _ts;

	SWSPacketHeartbeat() {}
	SWSPacketHeartbeat(SWPacket& other) {}

public:
	SWSPacketHeartbeat(SWHEADER* swheader, BYTE* data, uint64_t ts);
	virtual ~SWSPacketHeartbeat() {}

	virtual VOID Debug();
	virtual VOID Log();
	virtual VOID Do();
};