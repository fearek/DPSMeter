#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketMonsterInfo.h"
#include ".\Damage Meter\MySQLite.h"
SWPacketMonsterInfo::SWPacketMonsterInfo(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}
CHAR _name[64];

VOID SWPacketMonsterInfo::Do() {
	uint64_t offset = 0;
	uint16_t monsterAmount = *(uint16_t*)(_data+ sizeof(SWHEADER));
	offset += sizeof(uint16_t);
//LogInstance.WriteLog(const_cast<LPTSTR>(_T("Monster amount: %d\n")),monsterAmount);
	for (size_t i = 0; i < monsterAmount; i++)
	{
		SWPACKETMONSTERINFO* obj_create = (SWPACKETMONSTERINFO*)(_data + sizeof(SWHEADER) + offset);
		ZeroMemory(_name, MONSTER_NAME_LEN);
		SWDB.GetMonsterName(obj_create->_realDB2, _name, MONSTER_NAME_LEN);
	//	LogInstance.WriteLog(const_cast<LPTSTR>(_T("Monster id: %u realid: %u name: %s\n")),obj_create->_id,obj_create->_realDB2,_name);
		offset += sizeof(SWPACKETMONSTERINFO);
		DAMAGEMETER.InsertOwnerID(obj_create->_id, obj_create->_owner_id);
		DAMAGEMETER.InsertDB(obj_create->_id, obj_create->_realDB2);
	}
}

VOID SWPacketMonsterInfo::Log() {

}


VOID SWPacketMonsterInfo::Debug() {


	SWPACKETMONSTERINFO* obj_create = (SWPACKETMONSTERINFO*)(_data + sizeof(SWHEADER));

	//LogInstance.MyLog(_T("unknown02\n"));
	//for (int i = 0; i < 17; i++)
	//	LogInstance.MyLog(_T("%02x "), obj_create->_unknown02[i]);
	//LogInstance.MyLog(_T("\n"));

	//LogInstance.MyLog(_T("unknown03\n"));
	//for (int i = 0; i < 54; i++)
	//	LogInstance.MyLog(_T("%02x "), obj_create->_unknown03[i]);
	//LogInstance.MyLog(_T("\n"));

	//LogInstance.WriteLogA(const_cast<CHAR*>("[DEBUG] [Created Object] [X = %f] [Y = %f] [Z = %f]"), obj_create->_locationX, obj_create->_locationY, obj_create->_locationZ);
	//LogInstance.WriteLogA(const_cast<CHAR*>("[DEBUG] [Created Object] [X = %f] [Y = %f] [Z = %f]"), obj_create->_unknownFloat1, obj_create->_unknownFloat2, obj_create->_unknownFloat3);

	//LogInstance.MyLog(const_cast<CHAR*>("[DEBUG] [Created Object] [ID = %u] [Owner ID = %08x] [DB2 = %u] [RealDB2 = %u]\n"), obj_create->_id, obj_create->_owner_id, obj_create->_db2, obj_create->_realDB2);

	//LogInstance.WriteLogA(const_cast<CHAR*>("[DEBUG] [Created Object] [ID = %08x] [Owner ID = %08x] [DB2 = %u] [RealDB2 = %u]"), obj_create->_id, obj_create->_owner_id, obj_create->_db2, obj_create->_realDB2);
}