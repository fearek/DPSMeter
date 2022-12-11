#include "pch.h"
#include ".\Soulworker Packet\SWPacketCooldown.h"
#include ".\Buff Meter\Buff Meter.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketCooldown::SWPacketCooldown(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {
	
}

VOID SWPacketCooldown::Do() {
	SWPACKETCOOLDOWN* cooldown = (SWPACKETCOOLDOWN*)(_data + sizeof(SWHEADER));

	DAMAGEMETER.AddEnlighten(cooldown->_playerID, cooldown->_value);
}

VOID SWPacketCooldown::Log() {

}

VOID SWPacketCooldown::Debug() {

	SWPACKETCOOLDOWN* cooldown = (SWPACKETCOOLDOWN*)(_data + sizeof(SWHEADER));
	//LogInstance.MyLog(const_cast<LPTSTR>(_T("[DEBUG] [BUFF IN] [PLAYER ID = %08x] [value = %f] [Unknown = %u]\n")), cooldown->_playerID, cooldown->_value, cooldown->_unknown01);


	//LogInstance.MyLog(_T("buff info\n"));
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	LogInstance.MyLog(_T("%02x "), _data[i]);
	//LogInstance.MyLog(_T("\n"));

	//LogInstance.MyLog(const_cast<LPTSTR>(_T("[DEBUG] [BUFF IN] [PLAYER ID = %08x] [BUFF ID = %d] [BUFF STACK = %d] [DURATION = %f] [GIVER ID = %08x] [Unknown = %u]\n")), buff->_playerID, buff->_buffID, buff->_stack, buff->_duration, buff->_giverID, buff->_unknown01);

	//LogInstance.WriteLog(const_cast<LPTSTR>(_T("[DEBUG] [BUFF IN] [PLAYER ID = %08x] [BUFF ID = %d] [BUFF STACK = %d] [UNKNOWN = %f]")), buff->_playerID, buff->_buffID, buff->_stack, buff->_unknown01);
}