#include "pch.h"
#include ".\Soulworker Packet\SWCPresence.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\discord\DiscordPresence.h"
SWCPresence::SWCPresence(SWHEADER* swheader, BYTE* data) {
	_swheader = swheader;
	_data = data;
}

VOID SWCPresence::Do() {
	SWPACKET_PRESENCE* presencepacket = (SWPACKET_PRESENCE*)(_data + sizeof(SWHEADER));
	std::string utf8name;
	utf8name.assign((const char*)(_data+sizeof(SWHEADER)+sizeof(SWPACKET_PRESENCE)),presencepacket->nicklength);
	DISCORD.UpdatePresence(utf8name,presencepacket->maze,presencepacket->playerclass);
	return;
}

VOID SWCPresence::Log() {
	return;
}

VOID SWCPresence::Debug() {
	return;
}