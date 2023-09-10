#include "pch.h"
#include ".\Soulworker Packet\PacketType.h"
#include ".\Soulworker Packet\SWPacketMaker.h"
#include ".\Soulworker Packet\SWCPacket.h"
#include ".\UI\PlayerTable.h"
#include "SWConfig.h"
SOCKET new_socket;
SOCKET main_socket;
struct sockaddr_in address;
bool getBytes(std::vector<unsigned char>& buffer, unsigned int size)
{
	auto remaining = size;
	unsigned int hasread = 0;
	while (remaining > 0)
	{
		auto just_read = recv(new_socket, (char*)&buffer[hasread], remaining, 0);
		if (just_read == 0)
		{
			new_socket = INVALID_SOCKET;
			LogInstance.WriteLog("Module disconnected");
			return false;
		}
		if (just_read == -1)
		{
			new_socket = INVALID_SOCKET;
			LogInstance.WriteLog("Error in recv: %d", WSAGetLastError());
			return false;
		}
		else {
			remaining -= just_read;
			hasread += just_read;
		}
	}
	return true;
}
DWORD ReceiveCallback(LPVOID prc) {

	//handle connection and packets
	int max_sd, activity;
	fd_set readfds;
	while (true)
	{
		while (new_socket == INVALID_SOCKET) {
			FD_ZERO(&readfds);
			FD_SET(main_socket, &readfds);
			max_sd = main_socket;
			activity = select(NULL, &readfds, NULL, NULL, NULL);
			if (activity == SOCKET_ERROR)
			{
				DWORD error = WSAGetLastError();
				LogInstance.WriteLog("select failed: %d", error);
				exit(-1);
			}
			if (FD_ISSET(main_socket, &readfds))
			{
				int addrlen = sizeof(address);
				new_socket = accept(main_socket, (struct sockaddr*)&address, &addrlen);
				if (new_socket == INVALID_SOCKET)
				{
					int error = WSAGetLastError();
					LogInstance.WriteLog("Socket in thread failed: %d", error);
					exit(-1);
				}
				LogInstance.WriteLog("Module connected");
			}
			Sleep(100);
		}

		{
			std::vector<unsigned char> getsize;
			getsize.resize(4);
			if (getBytes(getsize, 4) == false) continue;
			unsigned short length = *(unsigned short*)&getsize[2];
			unsigned short packetlength = length - 4;
			std::vector<unsigned char> packet;
			packet.resize(packetlength);
			if (getBytes(packet, packetlength) == false) continue;
			std::vector<unsigned char> entirepacket; //who needs performance lmao
			entirepacket.reserve(length);
			entirepacket.insert(entirepacket.end(), getsize.begin(), getsize.end());
			entirepacket.insert(entirepacket.end(), packet.begin(), packet.end());
			SWPACKETMAKER.CreateSWPacket(entirepacket);
		}
	}
	return 0;
}
bool SWPacketMaker::Init() {
	WSADATA wsaData;
	//init connection
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		LogInstance.WriteLog("WSAStartup failed: %d", iResult);
		return iResult;
	}
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog("Socket failed: %d", error);
		return error;
	};
	int opt = TRUE;
	iResult = setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	if (iResult != 0)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog("setsockopt failed: %d", error);
		return error;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(21377);
	iResult = bind(main_socket, (struct sockaddr*)&address, sizeof(address));
	if (iResult != 0)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog("bind failed: %d", error);
		return error;
	}
	iResult = listen(main_socket, 1);
	if (iResult != 0)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog("listen failed: %d", error);
		return error;
	}
	HANDLE thread = CreateThread(NULL, 0, ReceiveCallback, this, 0, NULL);
	if (thread != NULL)
	{
		LogInstance.WriteLog("Module Listener Init");
		return ERROR_SUCCESS;
	}
	else
	{
		DWORD error = GetLastError();
		LogInstance.WriteLog("CreateThread failed: %d", error);
		return error;
	}
}
SWHEADER* SWPacketMaker::GetSWHeader(std::vector<unsigned char>& packet) {

	if (packet.size() < sizeof(SWHEADER)) {
		return nullptr;
	}


	SWHEADER* swheader = (SWHEADER*)(&packet[0]);
	//if (swheader->_magic != _SWMAGIC || (swheader->_const_value01 != 1 && swheader->_const_value01 != 2 )) {
	//	return nullptr;
	//}
	if (swheader->_const_value01 != 1 && swheader->_const_value01 != 2 && swheader->_const_value01 != 3)
	{
		return nullptr;
	}
	return swheader;

}

BYTE* SWPacketMaker::GetSWData(std::vector<unsigned char>& packet) {

	return (BYTE*)(&packet[0]);
}

VOID SWPacketMaker::CreateSWPacket(std::vector<unsigned char>& packet) {

	SWHEADER* swheader = GetSWHeader(packet);
	BYTE* data = GetSWData(packet);

	if (swheader == nullptr || data == nullptr)
	{
		return;
	}

#if DEBUG_RECV_DISPLAY_ALL_PKT == 1
	LogInstance.WriteLog("OP : %04x\tsize : %04x", swheader->_op, swheader->_size);
	for (int i = 0; i < swheader->_size; i++)
		LogInstance.WriteLogNoDate("%02x ", data[i]);
	LogInstance.WriteLogNoDate("\n\n");
#endif

	SWPacket* swpacket = nullptr;
	DAMAGEMETER.GetLock();
	{
		if(swheader->_const_value01 == 1) {
			switch (_byteswap_ushort(swheader->_op)) {


				/*0x03*/
			case RecvOPcode::STATCHANGE: //0430
				swpacket = new SWPacketStatChange(swheader, data);
				break;
			case RecvOPcode::DEAD:
				swpacket = new SWPacketDead(swheader, data);
				break;
			case RecvOPcode::CHARACTER_UPDATE_SPECIAL_OPTION_LIST:
				swpacket = new SWPacketCharacterUpdateSpecialOptionList(swheader, data);
				break;

				/*0x04*/
				// eSUB_CMD_WORLD_ENTER_RES
			case RecvOPcode::WORLDCHANGE: //0430
				swpacket = new SWPacketWorldChange(swheader, data);
				break;
			case RecvOPcode::MAZESTART:
				swpacket = new SWPacketMazeStart(swheader, data);
				break;
			case RecvOPcode::SPAWNED_CHARINFO:
				//swpacket = new SWPacketSpawnedCharInfo(swheader, data);
				break;
			case RecvOPcode::IN_INFO_MONSTER: //0605
				swpacket = new SWPacketInInfoMonster(swheader, data);
				break;
			case RecvOPcode::OTHER_INFOS_MONSTER:
				swpacket = new SWPacketMonsterInfo(swheader, data);
				break;

				/*0x05*/
			case RecvOPcode::STARTMOVE:
				//swpacket = new SWPacketStartMove(swheader, data);
				break;
			case RecvOPcode::STOPMOVE:
				break;
			case RecvOPcode::JUMP:
				break;
			case RecvOPcode::CANCEL_WITHMOVE:
				break;
			case RecvOPcode::ENTER_ANIMATION:
				swpacket = new SWPacketEnterAnimation(swheader, data);
				break;

				/*0x06 Combat*/
			//case RecvOPcode::EVADE:
			//	break;
			case RecvOPcode::USESKILL:
				//swpacket = new SWPacketUseSkill(swheader, data);
				break;
			case RecvOPcode::OTHER_USESKILL: //0430
				swpacket = new SWPacketOtherUseSkill(swheader, data);
				break;
			case RecvOPcode::DAMAGE: //0430
				swpacket = new SWPacketDamage(swheader, data);
				break;
			case RecvOPcode::BUFFIN: //0430
				swpacket = new SWPacketBuffIn(swheader, data);
				break;
			case RecvOPcode::BUFFOUT: //0430
				swpacket = new SWPacketBuffOut(swheader, data);
				break;
			case RecvOPcode::PROJECTILE:
				break;
			case RecvOPcode::AKASIC:
				swpacket = new SWPacketAkasic(swheader, data);
				break;
			case RecvOPcode::COOLDOWN: //0430
				swpacket = new SWPacketCooldown(swheader, data);
				break;

				/*0x07*/
			case RecvOPcode::CHAT:
				//swpacket = new SWPacketChat(swheader, data);
				break;

				/* 0x11 Maze*/
			case RecvOPcode::MAZEEND:
				swpacket = new SWPacketMazeEnd(swheader, data);
				break;
			case RecvOPcode::MAZE_UPDATE_STATE:
				swpacket = new SWPacketMazeUpdateState(swheader, data);
				break;

				/* 0x12 Party */
			case RecvOPcode::PARTY: //1117
				swpacket = new SWPacketParty(swheader, data);
				break;
			case RecvOPcode::PARTY_LIST_INFO:
				//swpacket = new SWPacketPartyListInfo(swheader, data);
				break;
			case RecvOPcode::SQUAD:
				swpacket = new SWPacketSquad(swheader, data);
				break;
				/* 0x17 Monster */
			case RecvOPcode::MONSTER_STAT_UPDATE:
				swpacket = new SWPacketMonsterStatUpdate(swheader, data);
				break;
			case RecvOPcode::MONSTER_KILLED: //0430
				swpacket = new SWPacketMonsterKilled(swheader, data);
				break;
			case RecvOPcode::AGGRO_CHANGED: //0430
				swpacket = new SWPacketAggroChanged(swheader, data);
				break;

				/* 0x23 Gesture*/
			case RecvOPcode::GESTURE_USED:
				//swpacket = new SWPacketGestureUsed(swheader, data);
				break;

				/* 0x2e Force*/
				// 8 players party
			case RecvOPcode::BIG_PARTY: //1117
				swpacket = new SWPacketBigParty(swheader, data);
				break;



			default:
#define DEBUG_RECV_DISPLAYPKT 1
#if DEBUG_RECV_DISPLAYPKT == 1
				LogInstance.WriteLog("OP : %04x\tsize : %04x", swheader->_op, swheader->_size);
				for (int i = 0; i < swheader->_size; i++) {
					LogInstance.WriteLogNoDate("%02x ", data[i]);
			}
				LogInstance.WriteLogNoDate("\n\n");
#endif
				break;
			}
		}
		else if (swheader->_const_value01 == 2)
		{
		switch (_byteswap_ushort(swheader->_op)) {
		case 0x0606:
			swpacket = new SWSPacketMyDodgeUsed(swheader, data);
			break;
		case 0x0608:
			swpacket = new SWSPacketMySkillUsed(swheader, data);
			break;
			}
		}
		else if (swheader->_const_value01 == 3)
		{
		switch (_byteswap_ushort(swheader->_op))
		{
		case 0x0101:
			swpacket = new SWCPing(swheader, data);
			break;
		case 0x0102:
			swpacket = new SWCPresence(swheader, data);
			break;
		}
		}
		else
		{
		DAMAGEMETER.FreeLock();
		return;
	}
		if (swpacket != nullptr) {
#if DEBUG_RECV_CREATEPACKET == 1
			swpacket->Debug();
#endif
			// Todo
			swpacket->Do();

			delete swpacket;
		}
	}
	DAMAGEMETER.FreeLock();

}