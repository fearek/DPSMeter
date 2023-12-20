#include "pch.h"
#include ".\Soulworker Packet\SWPacketHeartbeat.h"
#include ".\UI\PlayerTable.h"

SWPacketHeartbeat::SWPacketHeartbeat(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {
}

void SWPacketHeartbeat::Do() {
	

	
}

void SWPacketHeartbeat::Log() {

}

void SWPacketHeartbeat::Debug() {

	SWPACKETHEARTBEAT* hbData = (SWPACKETHEARTBEAT*)(_data + sizeof(SWHEADER));
	//LogInstance.WriteLog(_T("recv tick : %u / "), hbData->_tick);
	//for (int i = 0; i < sizeof(hbData->_unknown01); i++)
	//	LogInstance.MyLog(_T("%02x "), hbData->_unknown01[i]);
	//LogInstance.MyLog(_T("\n"));
}