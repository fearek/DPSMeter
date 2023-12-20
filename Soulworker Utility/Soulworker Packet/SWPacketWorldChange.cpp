#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketWorldChange.h"

SWPacketWorldChange::SWPacketWorldChange(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketWorldChange::Do() {
	
	DAMAGEMETER.Clear();

	SWPACKETWORLDCHANGE* world_change = (SWPACKETWORLDCHANGE*)(_data + sizeof(SWHEADER));

	DAMAGEMETER.SetMyID(world_change->_id);
	DAMAGEMETER.SetWorldID(world_change->_worldID);

	DAMAGEMETER.SetMazeState(false);
}

void SWPacketWorldChange::Log() {

}

void SWPacketWorldChange::Debug() {
	SWPACKETWORLDCHANGE* world_change = (SWPACKETWORLDCHANGE*)(_data + sizeof(SWHEADER));

	//LogInstance.WriteLog(const_cast<char*>("[DEBUG] [World Change = %04x] [MyID = %08x]"), world_change->_worldID, world_change->_id);
}