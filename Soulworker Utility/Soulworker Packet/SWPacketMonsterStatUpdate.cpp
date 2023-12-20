#include "pch.h"
#include ".\Soulworker Packet\SWPacketMonsterStatUpdate.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\PacketInfo.h"
#include ".\Damage Meter\MySQLite.h"
#include ".\UI\PlayerTable.h"
#include ".\Combat Meter\CombatMeter.h"

SWPacketMonsterStatUpdate::SWPacketMonsterStatUpdate(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketMonsterStatUpdate::Do() {

	int16_t offset = sizeof(SWHEADER);
	SWPacketMonsterStatUpdatePkt* pkt = (SWPacketMonsterStatUpdatePkt*)(_data + offset);
	offset += sizeof(SWPacketMonsterStatUpdatePkt);
	for (uint8_t i = 0; i < pkt->_statCounts; i++) {

		SWPacketMonsterStatData* pktStatData = (SWPacketMonsterStatData*)(_data + offset);
		offset += sizeof(SWPacketMonsterStatData);

		switch (pktStatData->_statID) {
		case StatType::CurrentHP:
			PLOTWINDOW.AddBossHpData(pkt->_id, pktStatData->_statVal, PLAYERTABLE.GetTableTime());
			break;
		}

		uint32_t monsterId = 0;
		SW_DB2_STRUCT* db = DAMAGEMETER.GetMonsterDB(pkt->_id);
		if (db != nullptr) {
			monsterId = db->_db2;
		}

		CombatLog* pCombatLog = new CombatLog;
		pCombatLog->_type = CombatLogType::CHANGED_STATS;
		pCombatLog->_val1 = pktStatData->_statID;
		pCombatLog->_val2 = static_cast<double>(pktStatData->_statVal);
		COMBATMETER.Insert(monsterId, CombatType::MONSTER, pCombatLog);
	}

}

void SWPacketMonsterStatUpdate::Log() {

}

void SWPacketMonsterStatUpdate::Debug() {

	/*int16_t offset = sizeof(SWHEADER);
	SWPacketMonsterStatUpdatePkt* pkt = (SWPacketMonsterStatUpdatePkt*)(_data + offset);
	offset += sizeof(SWPacketMonsterStatUpdatePkt);

	LogInstance.WriteLog("[SWPacketMonsterStatUpdate] MonsterId = %u, StatCount = %d", pkt->_id, pkt->_statCounts);

	for (uint8_t i = 0; i < pkt->_statCounts; i++) {

		SWPacketMonsterStatData* pktStatData = (SWPacketMonsterStatData*)(_data + offset);
		offset += sizeof(SWPacketMonsterStatData);

		LogInstance.WriteLogNoDate(L"%u : %llu : %.3f\n", pktStatData->_statID, pktStatData->_statVal, pktStatData->_unk01);

	}

	LogInstance.WriteLogNoDate(L"\n");*/
}