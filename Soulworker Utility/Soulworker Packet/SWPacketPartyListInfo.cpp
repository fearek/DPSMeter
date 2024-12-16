#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Soulworker Packet\SWPacketPartyListInfo.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketPartyListInfo::SWPacketPartyListInfo(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

void SWPacketPartyListInfo::Do() {


	//Log::MyLog("Party Info\n");
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	Log::MyLog("%02x ", _data[i]);
	//Log::MyLog("\n");

	BYTE* p_data = _data;
	p_data += sizeof(SWHEADER);
	BYTE partyCount = *p_data;
	//Log::MyLog("Party Counts : %u\n", partyCount);
	p_data += 1;

	//Log::MyLog("Unknown01 : %04x\n", *((unsigned short*)p_data));
	p_data += 2;
	//Log::MyLog("\n");

	for (int i = 0; i < partyCount; i++) {
		unsigned short unknown01 = *((unsigned short*)p_data);
		p_data += 2;

		BYTE unknown02 = *p_data;
		p_data += 1;

		unsigned short partyNameLength = *((unsigned short*)p_data);
		p_data += 2;

		wchar_t partyName_utf16[MAX_NAME_LEN] = { 0 };
		memcpy_s(partyName_utf16, MAX_NAME_LEN * sizeof(wchar_t), p_data, partyNameLength);
		char partyName_utf8[MAX_NAME_LEN] = { 0 };
		if (!UTF16toUTF8(partyName_utf16, partyName_utf8, MAX_NAME_LEN)) {
			//LogInstance.WriteLog("Error in SWPacketParty : UTF16toUTF8 FAILED");
			return;
		}
		p_data += partyNameLength;

		unsigned short minLv = *((unsigned short*)p_data);
		p_data += 2;
		unsigned short maxLv = *((unsigned short*)p_data);
		p_data += 2;

		BYTE unknown03 = *p_data;
		p_data += 1;

		unsigned short leaderNameLength = *((unsigned short*)p_data);
		p_data += 2;

		wchar_t leaderName_utf16[MAX_NAME_LEN] = { 0 };
		memcpy_s(leaderName_utf16, MAX_NAME_LEN * sizeof(wchar_t), p_data, leaderNameLength);
		char leaderName_utf8[MAX_NAME_LEN] = { 0 };
		if (!UTF16toUTF8(leaderName_utf16, leaderName_utf8, MAX_NAME_LEN)) {
			//LogInstance.WriteLog("Error in SWPacketParty : UTF16toUTF8 FAILED");
			return;
		}
		p_data += leaderNameLength;

		BYTE partyMemberCount = *p_data;
		p_data += 1;

		uint32_t remainedTime = *((uint32_t*)p_data);
		p_data += 4;

		unsigned short mapId = *((unsigned short*)p_data);
		p_data += 2;

		unsigned short unknown04 = *((unsigned short*)p_data);
		p_data += 2;

		uint32_t partyId = *((uint32_t*)p_data);
		p_data += 4;

		uint32_t leaderId = *((uint32_t*)p_data);
		p_data += 4;

		BYTE unknown05 = *p_data; // 1=teammates 2=enemy
		p_data += 1;
		BYTE unknown06 = *p_data;
		p_data += 1;

		//Log::MyLog("unknown 01 : %04x / 2: %02x / 3: %02x / 4 : %04x / 5 : %02x / 6 : %02x\n"
		//	, unknown01, unknown02, unknown03, unknown04, unknown05, unknown06);
		//Log::MyLog("Party Name : %s\n", partyName_utf16);
		//Log::MyLog("memberCounts : %u / minLvl : %u, maxLv : %u \n", partyMemberCount, minLv, maxLv);
		//Log::MyLog("Leader Name : %s / LeaderId : %u\n", leaderName_utf16, leaderId);
		//Log::MyLog("PartyId : %u / mapId : %u / remaindTime : %u \n", partyId, mapId, remainedTime);
		//Log::MyLog("\n");
	}
}

void SWPacketPartyListInfo::Log() {

}

void SWPacketPartyListInfo::Debug() {

	//SWPACKETPARTY_HEADER* party_header = (SWPACKETPARTY_HEADER*)(_data + sizeof(SWHEADER));

	//BYTE* p_data = _data;
	//p_data += sizeof(SWHEADER) + sizeof(SWPACKETPARTY_HEADER);

	//for (int i = 0; i < party_header->_partyPlayerCount; i++) {
	//	SWPACKETPARTY_DATA* party_data = (SWPACKETPARTY_DATA*)p_data;
	//	BYTE job = *(p_data + sizeof(SWPACKETPARTY_DATA) + party_data->_nickSize + 1);

	//	wchar_t utf16[MAX_NAME_LEN] = { 0 };
	//	memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), p_data + sizeof(SWPACKETPARTY_DATA), party_data->_nickSize);

	//	char utf8[MAX_NAME_LEN] = { 0 };
	//	if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
	//		//LogInstance.WriteLog("Error in SWPacketParty : UTF16toUTF8 FAILED");
	//		return;
	//	}

	//	//LogInstance.WriteLog("[DEBUG] [PARTY DATA] [PARTY PLAYER %d] [ID %08x] [NAME = %s] [NICKMEMSIZE = %d] [JOB = %d]", party_data->_playerID, utf16, party_data->_nickSize, job);

	//	p_data += sizeof(SWPACKETPARTY_DATA) + party_data->_nickSize + SWPACKETPARTY_DUMMY;
	//}
}