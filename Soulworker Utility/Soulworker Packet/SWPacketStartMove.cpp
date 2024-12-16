#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketStartMove.h"

SWPacketStartMove::SWPacketStartMove(SWHEADER* swheader, BYTE* data) {
	_swheader = swheader;
	_data = data;
}

void SWPacketStartMove::Do() {
	return;
}

void SWPacketStartMove::Log() {
	return;
}

void SWPacketStartMove::Debug() {

	//unsigned short op = _byteswap_unsigned short(_swheader->_op);
	//_SWPACKETSTARTMOVE* move = (_SWPACKETSTARTMOVE*)(_data + sizeof(SWHEADER));

	//if (_swheader->_op != 0x3403) {
	//	return;
	//}

	//printf("OP : %04x\tsize : %04x\n", op, _swheader->_size);

	//
	//for (int i = 0; i < _swheader->_size; i++)
	//	printf("%02x ", _data[i]);
	//printf("\n");

	//Log::MyLog("Unkown Packet : %04x\n", op);
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	Log::MyLog("%02x ", _data[i]);
	//Log::MyLog("\n");

	//Log::MyLog("player ID : %08x / map ID : %u / X : %f, Y : %f, Z : %f\n", move->_playerId, move->_mapId, move->_locationX, move->_locationY, move->_locationZ);
	//Log::MyLog("direction %f / endLocationX %f / endLocationX %f\n", move->_direction, move->_endLocationX, move->_endLocationY);
	//Log::MyLog("speed : %f\n ", move->_speed);

	//Log::MyLog("Unknown01 : ");
	//for (int i = 0; i < sizeof(move->_unknown01); i++) {
	//	Log::MyLog("%02x ", move->_unknown01[i]);
	//}
	//Log::MyLog(" / ");

	//Log::MyLog("Unknown02 : ");
	//for (int i = 0; i < sizeof(move->_unknown02); i++) {
	//	Log::MyLog("%02x ", move->_unknown02[i]);
	//}
	//Log::MyLog(" / ");

	//Log::MyLog("_screen : ");
	//for (int i = 0; i < sizeof(move->_screen); i++) {
	//	Log::MyLog("%02x ", move->_screen[i]);
	//}
	//Log::MyLog(" / \n");
	//
	//Log::MyLog("unknown 04 : %02x", move->_unknown04);

	//Log::MyLog(" / ");

	//Log::MyLog("Unknown05 : ");
	//for (int i = 0; i < sizeof(move->_unknown05); i++) {
	//	Log::MyLog("%02x ", move->_unknown05[i]);
	//}
	//Log::MyLog(" / \n");

	return;
}