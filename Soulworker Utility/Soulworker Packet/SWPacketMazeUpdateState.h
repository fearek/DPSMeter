#pragma once
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)

typedef struct _SWPacketMazeUpdateStatePacket {
	
	uint32_t _stateID;
	uint8_t _state;

}SWPacketMazeUpdateStatePacket;
#pragma pack(pop)

class SWPacketMazeUpdateState : public SWPacket {
protected:
	SWPacketMazeUpdateState() {}

public:
	SWPacketMazeUpdateState(SWHEADER* swheader, uint8_t* data);
	~SWPacketMazeUpdateState() {}

	void Do();
	void Log();
	void Debug();
};