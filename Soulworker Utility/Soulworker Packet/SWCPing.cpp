#include "pch.h"
#include ".\Soulworker Packet\SWCPing.h"
#include ".\Damage Meter\Damage Meter.h"
SWCPing::SWCPing(SWHEADER* swheader, uint8_t* data) {
	_swheader = swheader;
	_data = data;
}

void SWCPing::Do() {
	SWPACKET_PING* ping = (SWPACKET_PING*)(_data + sizeof(SWHEADER));
	DAMAGEMETER.SetPing(ping->_ping);

	return;
}

void SWCPing::Log() {
	return;
}

void SWCPing::Debug() {
	return;
}