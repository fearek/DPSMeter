#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketObjectCreate.h"
#include ".\Damage Meter\MySQLite.h"
#include <sstream>
SWPacketObjectCreate::SWPacketObjectCreate(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketObjectCreate::Do() {

	size_t offset = 0;
	SWPACKETOBJECTCREATE* obj_create = (SWPACKETOBJECTCREATE*)(_data + sizeof(SWHEADER));
	offset += sizeof(SWPACKETOBJECTCREATE);
	std::stringstream ss;
	for (size_t ii = 0; ii < obj_create->statamount; ii++)
	{

		unsigned char statid = *(unsigned char*)(_data + sizeof(SWHEADER) + offset);
		offset += 1;
		float statvalue = *(float*)(_data + sizeof(SWHEADER) + offset);
		offset += 4;
		ss << SWDB.GetStatName(statid) << ": " << statvalue << "\n";
	}
	if (DAMAGEMETER.shouldLogMstrStats) {
		char name[256] = { 0 };
		SWDB.GetMonsterName(obj_create->_realDB2, &name[0], 255);
		LogInstance.WriteLog("Name: %s Monster id: %u realid: %u owner: %X\nStats:\n", name, obj_create->_id, obj_create->_realDB2, obj_create->_owner_id);
		LogInstance.WriteLog("%s", ss.str().c_str());
	}
	offset += 21;
	DAMAGEMETER.InsertOwnerID(obj_create->_id, obj_create->_owner_id);
	DAMAGEMETER.InsertDB(obj_create->_id, obj_create->_realDB2);
}

VOID SWPacketObjectCreate::Log() {

}


VOID SWPacketObjectCreate::Debug() {


	SWPACKETOBJECTCREATE* obj_create = (SWPACKETOBJECTCREATE*)(_data + sizeof(SWHEADER));

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