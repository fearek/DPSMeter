#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)



#pragma pack(pop)

class SWPacketPartyListInfo : public SWPacket {
protected:
	SWPacketPartyListInfo() {}

public:
	SWPacketPartyListInfo(SWHEADER* swheader, BYTE* data);
	~SWPacketPartyListInfo() {}

	void Do();
	void Log();
	void Debug();
};