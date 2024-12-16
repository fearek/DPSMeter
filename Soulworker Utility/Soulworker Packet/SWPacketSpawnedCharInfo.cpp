#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketSpawnedcharInfo.h"

SWPacketSpawnedcharInfo::SWPacketSpawnedcharInfo(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

void SWPacketSpawnedcharInfo::Do() {

	SWPACKETSPAWNEDcharINFO_HEADER* spawned_header = (SWPACKETSPAWNEDcharINFO_HEADER*)(_data + sizeof(SWHEADER));

	BYTE* p_data = _data;
	p_data += sizeof(SWHEADER) + sizeof(SWPACKETSPAWNEDcharINFO_HEADER);

	BYTE job = *(p_data + spawned_header->_nameSize + 1);

	wchar_t utf16[MAX_NAME_LEN] = { 0 };
	memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), p_data, spawned_header->_nameSize);

	char utf8[MAX_NAME_LEN] = { 0 };
	if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
		//LogInstance.WriteLog("Error in SWPacketPos : UTF16toUTF8 FAILED");
		return;
	}


	//DAMAGEMETER.InsertPlayerMetadata(spawned_header->_playerId, utf8, job);

	//Log::MyLog("id : %d / nameSize : %u / name : %s / job : %u\n", spawned_header->_playerId, spawned_header->_nameSize, utf16, job);


}

void SWPacketSpawnedcharInfo::Log() {

}


void SWPacketSpawnedcharInfo::Debug() {


	//SWPACKETOBJECTCREATE* obj_create = (SWPACKETOBJECTCREATE*)(_data + sizeof(SWHEADER));

	//Log::MyLog("unknown02\n");
	//for (int i = 0; i < 17; i++)
	//	Log::MyLog("%02x ", obj_create->_unknown02[i]);
	//Log::MyLog("\n");

	//Log::MyLog("unknown03\n");
	//for (int i = 0; i < 54; i++)
	//	Log::MyLog("%02x ", obj_create->_unknown03[i]);
	//Log::MyLog("\n");

	//LogInstance.WriteLog(const_cast<char*>("[DEBUG] [Created Object] [X = %f] [Y = %f] [Z = %f]"), obj_create->_locationX, obj_create->_locationY, obj_create->_locationZ);
	//LogInstance.WriteLog(const_cast<char*>("[DEBUG] [Created Object] [X = %f] [Y = %f] [Z = %f]"), obj_create->_unknownfloat1, obj_create->_unknownfloat2, obj_create->_unknownfloat3);


	//LogInstance.WriteLog(const_cast<char*>("[DEBUG] [Created Object] [ID = %08x] [Owner ID = %08x] [DB2 = %u] [RealDB2 = %u]"), obj_create->_id, obj_create->_owner_id, obj_create->_db2, obj_create->_realDB2);
}