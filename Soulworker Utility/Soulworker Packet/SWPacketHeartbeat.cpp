#include "pch.h"
#include ".\Soulworker Packet\SWPacketHeartbeat.h"
#include ".\UI\PlayerTable.h"

SWPacketHeartbeat::SWPacketHeartbeat(SWHEADER* swheader, BYTE* data, uint64_t ts) : SWPacket(swheader, data), _ts(ts) {
}

void SWPacketHeartbeat::Do() {
	
	SWPACKETHEARTBEAT* hbData = (SWPACKETHEARTBEAT*)(_data + sizeof(SWHEADER));

	if (PLAYERTABLE._tick == hbData->_tick) {
		PLAYERTABLE._ping = _ts - PLAYERTABLE._lastSendTimestamp;
	}
}

void SWPacketHeartbeat::Log() {

}

void SWPacketHeartbeat::Debug() {

	SWPACKETHEARTBEAT* hbData = (SWPACKETHEARTBEAT*)(_data + sizeof(SWHEADER));
	//LogInstance.WriteLog("recv tick : %u / ", hbData->_tick);
	//for (int i = 0; i < sizeof(hbData->_unknown01); i++)
	//	Log::MyLog("%02x ", hbData->_unknown01[i]);
	//Log::MyLog("\n");
}