#include "pch.h"
#include ".\Soulworker Packet\SWPacketAggroChanged.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketAggroChanged::SWPacketAggroChanged(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

void SWPacketAggroChanged::Do() {

	SWPACKETAGGROCHANGED* aggro_data = (SWPACKETAGGROCHANGED*)(_data + sizeof(SWHEADER));
	DAMAGEMETER.SetAggro(aggro_data->_id, aggro_data->_targetedId);

}

void SWPacketAggroChanged::Log() {

}

void SWPacketAggroChanged::Debug() {
	SWPACKETAGGROCHANGED* aggro_data = (SWPACKETAGGROCHANGED*)(_data + sizeof(SWHEADER));

	//Log::MyLog("Aggro Packet\n");
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	Log::MyLog("%02x ", _data[i]);
	//Log::MyLog("\n");
	//Log::MyLog("ID : %u / Targeted : %u\n", aggro_data->_id, aggro_data->_targetedId);

	//Log::MyLog("ID : %u / Targeted : %u", aggro_data->_id, aggro_data->_targetedId);
}