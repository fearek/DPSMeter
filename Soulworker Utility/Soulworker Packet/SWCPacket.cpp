#include "pch.h"
#include ".\Soulworker Packet\SWCPacket.h"
SWCPacket::SWCPacket(SWCHEADER* swheader, uint8_t* data) {
	_swheader = swheader;
	_data = data;
}

void SWCPacket::Do() {
	return;
}

void SWCPacket::Log() {
	return;
}

void SWCPacket::Debug() {


	uint16_t op = _byteswap_ushort(_swheader->_op);



	return;
}