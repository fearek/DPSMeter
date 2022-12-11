#include "pch.h"
#include ".\Soulworker Packet\SWPacketBuffIn.h"
#include ".\Buff Meter\Buff Meter.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\UI\PlotWindow.h"
#include ".\Combat Meter\CombatMeter.h"

SWPacketBuffIn::SWPacketBuffIn(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketBuffIn::Do() {

	BUFFMETER.GetLock();
	{

		SWPACKETBUFFIN* buff = (SWPACKETBUFFIN*)(_data + sizeof(SWHEADER));

		if (DAMAGEMETER.CheckPlayer(buff->_playerID)) {
			DAMAGEMETER.BuffIn(buff->_playerID, buff->_buffID, buff->_stack, buff->_giverID);
			BUFFMETER.AddBuff(buff->_playerID, buff->_buffID, buff->_stack);

			// Desire, LG loop send this packet BRUH
			if (buff->_buffID != 43104 && buff->_buffID != 43105)
			{
				CombatLog* pCombatLog = new CombatLog;
				pCombatLog->_type = CombatLogType::BUFF_STARTED;
				pCombatLog->_val1 = buff->_buffID;
				pCombatLog->_val2 = buff->_stack;
				COMBATMETER.Insert(buff->_playerID, CombatType::PLAYER, pCombatLog);
			}
		}

		//LogInstance.MyLog(const_cast<LPTSTR>(_T("[DEBUG] [BUFF IN] [PLAYER ID = %08x] [BUFF ID = %d] [BUFF STACK = %d] [DURATION = %f] [GIVER ID = %08x] [Unknown = %u]\n")), buff->_playerID, buff->_buffID, buff->_stack, buff->_duration, buff->_giverID, buff->_unknown01);
	}
	BUFFMETER.FreeLock();


}

VOID SWPacketBuffIn::Log() {

}

VOID SWPacketBuffIn::Debug() {

	SWPACKETBUFFIN* buff = (SWPACKETBUFFIN*)(_data + sizeof(SWHEADER));

	//LogInstance.MyLog(_T("buff info\n"));
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	LogInstance.MyLog(_T("%02x "), _data[i]);
	//LogInstance.MyLog(_T("\n"));

	//LogInstance.MyLog(_T("[DEBUG] [BUFF IN] [PLAYER ID = %08x] [BUFF ID = %d] [BUFF STACK = %d] [DURATION = %f] [GIVER ID = %08x] [Unknown = %u]\n"), buff->_playerID, buff->_buffID, buff->_stack, buff->_duration, buff->_giverID, buff->_unknown01);
}