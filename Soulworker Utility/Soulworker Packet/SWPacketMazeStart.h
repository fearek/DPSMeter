#pragma once
#include ".\Soulworker Packet\SWPacket.h"

class SWPacketMazeStart : public SWPacket {
protected:
	SWPacketMazeStart() {}

public:
	SWPacketMazeStart(SWHEADER* swheader, uint8_t* data);
	~SWPacketMazeStart() {}

	void Do();
	void Log();
	void Debug();
};