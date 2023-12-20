#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketChat.h"

SWPacketChat::SWPacketChat(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketChat::Do() {
	SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	uint8_t* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);
}

void SWPacketChat::Log() {

}

void SWPacketChat::Debug() {
	
	//SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	//uint8_t* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);

	//wchar_t utf16[MAX_NAME_LEN] = { 0 };
	//memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), p_data, chat_header->_chatSize);

	//char utf8[MAX_NAME_LEN] = { 0 };
	//if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
	//	//LogInstance.WriteLog(const_cast<LPTSTR>(_T("Error in SWPacketChat : UTF16toUTF8 FAILED")));
	//	return;
	//}

	//LogInstance.MyLog(const_cast<LPTSTR>(_T("[DEBUG] [CHAT] [ID %d] [ChatType = %d] [unknown1 = %02x] [unknown2 = %04x] [chatSize = %d] [chat = %s]\n")), 
	//chat_header->_playerID, chat_header->_chatType, chat_header->_unknown01, chat_header->_unknown02, chat_header->_chatSize, utf16);

}