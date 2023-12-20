#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketUseSkill.h"

SWPacketUseSkill::SWPacketUseSkill(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketUseSkill::Do() {
	//	SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	//	uint8_t* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);
}

void SWPacketUseSkill::Log() {

}

void SWPacketUseSkill::Debug() {

	//LogInstance.MyLog(_T("UseSkill Packet\n"));
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	LogInstance.MyLog(_T("%02x "), _data[i]);
	//LogInstance.MyLog(_T("\n"));

}