#pragma once

#include ".\Soulworker Packet\PacketType.h"
#include ".\Soulworker Packet\SWPacket.h"

#define SWPACKETMAKER SWPacketMaker::getInstance()

#ifdef _DEBUG
#define DEBUG_RECV_CREATEPACKET 0
#define DEBUG_RECV_DISPLAYPKT 0
#define DEBUG_RECV_DISPLAY_ALL_PKT 0
#endif

class SWPacketMaker : public Singleton<SWPacketMaker> {
private:
	

public:


	bool Init();
	SWHEADER* GetSWHeader(std::vector<unsigned char>& packet);
	void CreateSWPacket(std::vector<unsigned char>& packet);
};