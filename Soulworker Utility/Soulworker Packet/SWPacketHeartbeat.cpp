#include "pch.h"
#include ".\Soulworker Packet\SWPacketHeartbeat.h"
#include ".\UI\PlayerTable.h"

SWPacketHeartbeat::SWPacketHeartbeat(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {
}

VOID SWPacketHeartbeat::Do() {
	

	
}

VOID SWPacketHeartbeat::Log() {

}

VOID SWPacketHeartbeat::Debug() {

	SWPACKETHEARTBEAT* hbData = (SWPACKETHEARTBEAT*)(_data + sizeof(SWHEADER));
	//LogInstance.WriteLog(_T("recv tick : %u / "), hbData->_tick);
	//for (int i = 0; i < sizeof(hbData->_unknown01); i++)
	//	LogInstance.MyLog(_T("%02x "), hbData->_unknown01[i]);
	//LogInstance.MyLog(_T("\n"));
}