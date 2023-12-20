#include "pch.h"
#include ".\Soulworker Packet\SWPacketCharacterUpdateSpecialOptionList.h"
#include ".\Buff Meter\Buff Meter.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\UI\PlotWindow.h"
#include ".\Combat Meter\CombatMeter.h"

SWPacketCharacterUpdateSpecialOptionList::SWPacketCharacterUpdateSpecialOptionList(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketCharacterUpdateSpecialOptionList::Do() {

	if (DAMAGEMETER.isTownMap()) {
		return;
	}

	int16_t offset = sizeof(SWHEADER);
	SWPacketCharacterUpdateSpecialOptionListHeader* listPacket = (SWPacketCharacterUpdateSpecialOptionListHeader*)(_data + offset);
	offset += sizeof(SWPacketCharacterUpdateSpecialOptionListHeader);

	for (uint8_t i = 0; i < listPacket->_listCount; i++)
	{
		SWPacketCharacterUpdateSpecialOptionVal* valPacket = (SWPacketCharacterUpdateSpecialOptionVal*)(_data + offset);
		offset += sizeof(SWPacketCharacterUpdateSpecialOptionVal);

		if (valPacket->_listID >= SpecialStatType::End)
		{
#if _DEBUG
			LogInstance.WriteLog("[SWPacketCharacterUpdateSpecialOptionList] Find Unknown statType = %x, statValue = %f", valPacket->_listID, valPacket->_listVal);
#endif
			continue;
		}

		DAMAGEMETER.UpdateSpecialStat(listPacket->_playerID, valPacket->_listID, valPacket->_listVal);

		CombatLog* pCombatLog = new CombatLog;
		pCombatLog->_type = CombatLogType::CHANGED_SPECIAL_STATS;
		pCombatLog->_val1 = valPacket->_listID;
		pCombatLog->_val2 = valPacket->_listVal;
		COMBATMETER.Insert(listPacket->_playerID, CombatType::PLAYER, pCombatLog);
	}
}

void SWPacketCharacterUpdateSpecialOptionList::Log() {

}

void SWPacketCharacterUpdateSpecialOptionList::Debug() {

	/*int16_t offset = sizeof(SWHEADER);
	SWPacketCharacterUpdateSpecialOptionListHeader* listPacket = (SWPacketCharacterUpdateSpecialOptionListHeader*)(_data + offset);
	offset += sizeof(SWPacketCharacterUpdateSpecialOptionListHeader);

	if (listPacket->_playerID != DAMAGEMETER.GetMyID())
		return;

	for (uint8_t i = 0; i < listPacket->_listCount; i++)
	{
		SWPacketCharacterUpdateSpecialOptionVal* valPacket = (SWPacketCharacterUpdateSpecialOptionVal*)(_data + offset);
		offset += sizeof(SWPacketCharacterUpdateSpecialOptionVal);

		LogInstance.WriteLog("[SWPacketCharacterUpdateSpecialOptionList] listID = %d, listVal = %.f", valPacket->_listID, valPacket->_listVal);

	}*/
}