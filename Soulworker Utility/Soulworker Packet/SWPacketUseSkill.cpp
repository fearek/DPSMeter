#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketUseSkill.h"

SWPacketUseSkill::SWPacketUseSkill(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

void SWPacketUseSkill::Do() {
	//	SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	//	BYTE* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);
}

void SWPacketUseSkill::Log() {

}

void SWPacketUseSkill::Debug() {

	//Log::MyLog("UseSkill Packet\n");
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	Log::MyLog("%02x ", _data[i]);
	//Log::MyLog("\n");

}