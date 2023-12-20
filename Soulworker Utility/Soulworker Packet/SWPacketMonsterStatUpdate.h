#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPacketMonsterStatUpdate {
	uint32_t _id;
	uint8_t _statCounts;
}SWPacketMonsterStatUpdatePkt;

typedef struct _SWPacketMonsterStatData {
	float _unk01;
	uint16_t _statID;
	uint64_t _statVal;
}SWPacketMonsterStatData;
#pragma pack(pop)

class SWPacketMonsterStatUpdate : public SWPacket {

protected:
	SWPacketMonsterStatUpdate() {}

public:
	SWPacketMonsterStatUpdate(SWHEADER* swheader, uint8_t* data);
	~SWPacketMonsterStatUpdate() {}

	void Do();
	void Debug();
	void Log();
};