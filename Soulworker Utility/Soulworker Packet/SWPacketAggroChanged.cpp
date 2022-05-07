#include "pch.h"
#include ".\Soulworker Packet\SWPacketAggroChanged.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketAggroChanged::SWPacketAggroChanged(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketAggroChanged::Do() {

	SWPACKETAGGROCHANGED* aggro_data = (SWPACKETAGGROCHANGED*)(_data + sizeof(SWHEADER));
	DAMAGEMETER.SetAggro(aggro_data->_id, aggro_data->_targetedId);

}

VOID SWPacketAggroChanged::Log() {

}

VOID SWPacketAggroChanged::Debug() {
	SWPACKETAGGROCHANGED* aggro_data = (SWPACKETAGGROCHANGED*)(_data + sizeof(SWHEADER));

	//LogInstance.MyLog(_T("Aggro Packet\n"));
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	LogInstance.MyLog(_T("%02x "), _data[i]);
	//LogInstance.MyLog(_T("\n"));
	//LogInstance.MyLog(_T("ID : %u / Targeted : %u\n"), aggro_data->_id, aggro_data->_targetedId);

	//LogInstance.MyLog(_T("ID : %u / Targeted : %u"), aggro_data->_id, aggro_data->_targetedId);
}