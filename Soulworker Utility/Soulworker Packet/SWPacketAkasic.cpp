#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketAkasic.h"

SWPacketAkasic::SWPacketAkasic(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketAkasic::Do() {

	SWPACKETAKASIC* akasic = (SWPACKETAKASIC*)(_data + sizeof(SWHEADER));

	DAMAGEMETER.InsertOwnerID(akasic->_id, akasic->_ownder_id);
}

void SWPacketAkasic::Log() {

}

void SWPacketAkasic::Debug() {
	SWPACKETAKASIC* akasic = (SWPACKETAKASIC*)(_data + sizeof(SWHEADER));

	//LogInstance.WriteLog(const_cast<char*>("[DEBUG] [Akasic] [ID = %08x] [Owner ID = %08x]"), akasic->_id, akasic->_ownder_id);
}