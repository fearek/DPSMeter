#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Soulworker Packet\SWPacketSquad.h"

SWPacketSquad::SWPacketSquad(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

void SWPacketSquad::Do() {

	size_t offset = sizeof(SWHEADER); //SWHEADER

	offset += 12; //unk01

	uint16_t msgLen = 0; //RECRUITMSG
	memcpy(&msgLen, _data + offset, 2);

	offset += 2; //msgLen

	offset += msgLen; //Recruitment message

	uint16_t squadLeaderNickSize = 0;
	memcpy(&squadLeaderNickSize, _data + offset, 2);

	offset += 2; //SQUADLEADERNICKSIZE

	offset += squadLeaderNickSize; //SQUADLEADERNICK

	offset += 12; //unk02

	uint8_t squadPlayerCount = 0;
	memcpy(&squadPlayerCount, _data + offset, 1);

	offset += 1; //SQUADPLAYERCOUNT

	offset += 3; //unk03

	for (int i = 0; i < squadPlayerCount; i++) {
		uint32_t playerId = 0;
		memcpy(&playerId, _data + offset, 4);

		offset += 4; //PLAYERID

		uint16_t playerNickSize = 0;
		memcpy(&playerNickSize, _data + offset, 2);

		offset += 2; //PLAYERNICKSIZE

		wchar_t utf16[MAX_NAME_LEN] = { 0 };
		memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), _data + offset, playerNickSize);

		char utf8[MAX_NAME_LEN] = { 0 };
		if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
			// LogInstance.WriteLog("Error in SWPacketSquad : UTF16toUTF8 FAILED");
			return;
		}

		offset += playerNickSize; //PLAYERNICK

		offset += 1; //D_unk01
		uint8_t playerJob = 0;
		memcpy(&playerJob, _data + offset, 1);

		DAMAGEMETER.InsertPlayerMetadata(playerId, utf8, playerJob);

		offset += 1; //PLAYERJOB

		offset += 62; //D_unk02
	}
}

void SWPacketSquad::Log() {

	size_t offset = sizeof(SWHEADER); //SWHEADER

	LogInstance.WriteLog("Skipping past unk01 (12 bytes)");
	offset += 12; //unk01

	LogInstance.WriteLog("At offset %zu", offset);
	uint16_t msgLen = 0; //RECRUITMSG
	memcpy(&msgLen, _data + offset, 2);

	offset += 2; //msgLen

	LogInstance.WriteLog("At offset %zu", offset);
	wchar_t utf16[MAX_NAME_LEN] = { 0 };
	memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), _data + offset, msgLen);
	char utf8[MAX_NAME_LEN] = { 0 };
	if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
		LogInstance.WriteLog("Failed to convert recruitment message");
	}
	else {
		LogInstance.WriteLog("Recruitment message is %s (%04x bytes)", utf8, msgLen);
	}

	offset += msgLen; //Recruitment message

	LogInstance.WriteLog("At offset %zu", offset);

	uint16_t squadLeaderNickSize = 0;
	memcpy(&squadLeaderNickSize, _data + offset, 2);
	LogInstance.WriteLog("Found leader nick size of %04x (2 bytes)", squadLeaderNickSize);

	offset += 2; //SQUADLEADERNICKSIZE

	LogInstance.WriteLog("At offset %zu skip leader name for now", offset);
	memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), _data + offset, squadLeaderNickSize);
	memset(utf16, 0, sizeof(utf16));
	memset(utf8, 0, sizeof(utf8));
	if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
		LogInstance.WriteLog("Failed to convert squad leader name");
	}
	else {
		LogInstance.WriteLog("Squad leader name is %s (%04x bytes)", utf8, squadLeaderNickSize);
	}

	offset += squadLeaderNickSize; //SQUADLEADERNICK

	LogInstance.WriteLog("At offset %zu", offset);
	LogInstance.WriteLog("Skipping past unk02 (12 bytes)");
	offset += 12; //unk02

	LogInstance.WriteLog("At offset %zu", offset);
	uint8_t squadPlayerCount = 0;
	memcpy(&squadPlayerCount, _data + offset, 1);
	LogInstance.WriteLog("Squad player count is %02x (1 byte)", squadPlayerCount);

	offset += 1; //SQUADPLAYERCOUNT

	LogInstance.WriteLog("At offset %zu skipping past unk03 (3 bytes)", offset);

	offset += 3; //unk03

	for (int i = 0; i < squadPlayerCount; i++) {
		uint32_t playerId = 0;
		memcpy(&playerId, _data + offset, 4);
		LogInstance.WriteLog("Found player ID %08x (4 bytes)", playerId);

		offset += 4; //PLAYERID
		LogInstance.WriteLog("At offset %zu", offset);

		uint16_t playerNickSize = 0;
		memcpy(&playerNickSize, _data + offset, 2);
		LogInstance.WriteLog("Found player nick size of %04x (2 bytes)", playerNickSize);

		offset += 2; //PLAYERNICKSIZE
		LogInstance.WriteLog("At offset %zu", offset);

		memset(utf16, 0, sizeof(utf16));
		memset(utf8, 0, sizeof(utf8));
		memcpy_s(utf16, MAX_NAME_LEN * sizeof(wchar_t), _data + offset, playerNickSize);
		utf16[playerNickSize] = 0;
		if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
			LogInstance.WriteLog("Failed to convert player name");
		}
		else {
			LogInstance.WriteLog("Player name is %s", utf8);
		}

		offset += playerNickSize; //PLAYERNICK

		LogInstance.WriteLog("At offset %zu skipping past D_unk01 (1 byte)", offset);

		offset += 1; //D_unk01

		LogInstance.WriteLog("At offset %zu", offset);
		uint8_t playerJob = 0;
		memcpy(&playerJob, _data + offset, 1);
		LogInstance.WriteLog("Player job is %02x (1 byte)", playerJob);

		offset += 1; //PLAYERJOB

		LogInstance.WriteLog("Skipping past D_unk02 (62 bytes)");

		offset += 62; //D_unk02
	}

}

void SWPacketSquad::Debug() {

}