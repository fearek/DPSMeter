#include "pch.h"
#include ".\Soulworker Packet\SWCPacket.h"
SWCPacket::SWCPacket(SWCHEADER* swheader, BYTE* data) {
	_swheader = swheader;
	_data = data;
}

VOID SWCPacket::Do() {
	return;
}

VOID SWCPacket::Log() {
	return;
}

VOID SWCPacket::Debug() {


	USHORT op = _byteswap_ushort(_swheader->_op);



	return;
}