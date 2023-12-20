#include "pch.h"
#include ".\Soulworker Packet\SWSPacketMyDodgeUsed.h"
#include ".\Damage Meter\Damage Meter.h"

SWSPacketMyDodgeUsed::SWSPacketMyDodgeUsed(SWHEADER* swheader, uint8_t* data) {
	_swheader = swheader;
	_data = data;
}

void SWSPacketMyDodgeUsed::Do() {
	SWPACKET_MYDODGEUSED* dodgeUsed = (SWPACKET_MYDODGEUSED*)(_data + sizeof(SWHEADER));

	// check is it normal dodge (ground dodge) as rolling (roll after down) is also there
	if (normalDodgeList.find(dodgeUsed->_skillId) == normalDodgeList.end()) {
		return;
	}

	DAMAGEMETER.AddDodgeUsed(dodgeUsed->_playerId);

	return;
}

void SWSPacketMyDodgeUsed::Log() {
	return;
}

void SWSPacketMyDodgeUsed::Debug() {
	return;
}