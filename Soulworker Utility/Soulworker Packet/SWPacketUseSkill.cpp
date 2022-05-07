#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketUseSkill.h"

SWPacketUseSkill::SWPacketUseSkill(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketUseSkill::Do() {
	//	SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	//	BYTE* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);
}

VOID SWPacketUseSkill::Log() {

}

VOID SWPacketUseSkill::Debug() {

	//LogInstance.MyLog(_T("UseSkill Packet\n"));
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	LogInstance.MyLog(_T("%02x "), _data[i]);
	//LogInstance.MyLog(_T("\n"));

}