#include "pch.h"
#include ".\Soulworker Packet\SWCPing.h"
#include ".\Damage Meter\Damage Meter.h"
SWCPing::SWCPing(SWHEADER* swheader, BYTE* data) {
	_swheader = swheader;
	_data = data;
}

VOID SWCPing::Do() {
	SWPACKET_PING* ping = (SWPACKET_PING*)(_data + sizeof(SWHEADER));
	DAMAGEMETER.SetPing(ping->_ping);

	return;
}

VOID SWCPing::Log() {
	return;
}

VOID SWCPing::Debug() {
	return;
}