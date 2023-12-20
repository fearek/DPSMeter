#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETCHAT_HEADER {
	uint32_t _playerID;
	uint8_t _chatType;
	uint8_t _unknown01;
	uint16_t _unknown02;
	uint16_t _chatSize;
}SWPACKETCHAT_HEADER;
#pragma pack(pop)

class SWPacketChat : public SWPacket {

protected:
	SWPacketChat() {}

public:
	SWPacketChat(SWHEADER* swheader, uint8_t* data);
	~SWPacketChat() {}

	void Do();
	void Debug();
	void Log();
};