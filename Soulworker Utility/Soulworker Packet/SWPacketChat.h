#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETCHAT_HEADER {
	uint32_t _playerID;
	BYTE _chatType;
	BYTE _unknown01;
	unsigned short _unknown02;
	unsigned short _chatSize;
}SWPACKETCHAT_HEADER;
#pragma pack(pop)

class SWPacketChat : public SWPacket {

protected:
	SWPacketChat() {}

public:
	SWPacketChat(SWHEADER* swheader, BYTE* data);
	~SWPacketChat() {}

	void Do();
	void Debug();
	void Log();
};