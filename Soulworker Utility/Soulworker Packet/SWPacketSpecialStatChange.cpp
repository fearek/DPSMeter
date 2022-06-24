#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Soulworker Packet\SWPacketSpecialStatChange.h"
#include ".\Damage Meter\Damage Meter.h"


SWPacketSpecialStatChange::SWPacketSpecialStatChange(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketSpecialStatChange::Do() {

	USHORT worldID = DAMAGEMETER.GetWorldID();
	//if (worldID == 0 || worldID == 10003 || worldID == 10021 || worldID == 10031 || worldID == 10041 || worldID == 11001 || worldID == 10051 || worldID == 10061 || worldID == 20011) {
	//	return;
	//}

	SWPACKETSPECIALSTATCHANGE_HEADER* stat_header = (SWPACKETSPECIALSTATCHANGE_HEADER*)(_data + sizeof(SWHEADER));

	BYTE* p_data;
		p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETSPECIALSTATCHANGE_HEADER);
		LogInstance.WriteLog("Stats count: %d",stat_header->_statsCount);
	for (int i = 0; i < stat_header->_statsCount; i++) {
		SWPACKETSPECIALSTATCHANGE_DATA* stat_data = (SWPACKETSPECIALSTATCHANGE_DATA*)p_data;
		LogInstance.WriteLog("[DEBUG] SPECIALSTAT[ID %08x] [statType = %x], [statValue = %f]\n", stat_header->_playerID, stat_data->_statType, stat_data->_statValue);
		DAMAGEMETER.UpdateSpecialStat(stat_header->_playerID, stat_data->_statType, stat_data->_statValue);
		p_data += sizeof(SWPACKETSPECIALSTATCHANGE_DATA);
	}
}

VOID SWPacketSpecialStatChange::Log() {

}

VOID SWPacketSpecialStatChange::Debug() {
	SWPACKETSPECIALSTATCHANGE_HEADER* stat_header = (SWPACKETSPECIALSTATCHANGE_HEADER*)(_data + sizeof(SWHEADER));

	BYTE* p_data;
	
		p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETSPECIALSTATCHANGE_HEADER);

	for (int i = 0; i < stat_header->_statsCount; i++) {
		SWPACKETSPECIALSTATCHANGE_DATA* stat_data = (SWPACKETSPECIALSTATCHANGE_DATA*)p_data;

		DAMAGEMETER.UpdateStat(stat_header->_playerID, stat_data->_statType, stat_data->_statValue);
		//LogInstance.MyLog(_T("[DEBUG] SPECIALSTAT[ID %08x] [statType = %x], [statValue = %f]\n"), stat_header->_playerID, stat_data->_statType, stat_data->_statValue);
		p_data += sizeof(SWPACKETSPECIALSTATCHANGE_DATA);

	}
}