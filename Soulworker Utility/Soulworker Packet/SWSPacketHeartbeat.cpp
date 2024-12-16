#include "pch.h"
#include ".\Soulworker Packet\SWSPacketHeartbeat.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\UI\PlayerTable.h"

SWSPacketHeartbeat::SWSPacketHeartbeat(SWSHEADER* swheader, BYTE* data, uint64_t ts) {
	_swheader = swheader;
	_data = data;
	_ts = ts;
}

VOID SWSPacketHeartbeat::Do() {
	_SWSPACKET_HEARTBEAT* hbData = (_SWSPACKET_HEARTBEAT*)(_data + sizeof(SWSHEADER));

	PLAYERTABLE._lastSendTimestamp = _ts;
	PLAYERTABLE._tick = hbData->_tick;

	return;
}

VOID SWSPacketHeartbeat::Log() {
	return;
}

VOID SWSPacketHeartbeat::Debug() {
	_SWSPACKET_HEARTBEAT* hbData = (_SWSPACKET_HEARTBEAT*)(_data + sizeof(SWSHEADER));
	//LogInstance.WriteLog(_T("send tick : %u / "), hbData->_tick);
	return;
}