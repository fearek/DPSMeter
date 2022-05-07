#include "pch.h"
#include <Winsock2.h>
#include ".\Packet Capture\MyWinDivert.h"
#include ".\Soulworker Packet\SWPacketMaker.h"
SOCKET new_socket = INVALID_SOCKET;
SOCKET main_socket = INVALID_SOCKET;
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
			LogInstance.WriteLog(const_cast<LPTSTR>(_T("Module disconnected")));
			return false;
		}
		if (just_read == -1)
		{
			new_socket = INVALID_SOCKET;
			LogInstance.WriteLog(const_cast<LPTSTR>(_T("Error in recv: %d")), WSAGetLastError());
			return false;
		}
		else {
			remaining -= just_read;
			hasread += just_read;
		}
	}
	return true;
}
struct sockaddr_in address;
DWORD MyWinDivert::Init() {

	WSADATA wsaData;
	//init connection
	int iResult = WSAStartup(MAKEWORD(2, 2),&wsaData);
	if (iResult != 0) {
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("WSAStartup failed: %d")), iResult);
		return iResult;
	}
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (main_socket == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("Socket failed: %d")), error);
		return error;
	};
	int opt = TRUE;
	iResult = setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR,(char*)&opt,sizeof(opt));
	if (iResult != 0)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("setsockopt failed: %d")), error);
		return error;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(21377);
	iResult = bind(main_socket, (struct sockaddr*)&address, sizeof(address));
	if(iResult != 0)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("bind failed: %d")), error);
		return error;
	}
	iResult = listen(main_socket, 1);
	if (iResult != 0)
	{
		int error = WSAGetLastError();
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("listen failed: %d")), error);
		return error;
	}
	HANDLE thread = CreateThread(NULL, 0, ReceiveCallback, this, 0, NULL);
	if (thread != NULL)
	{
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("Module Listener Init")));
		return ERROR_SUCCESS;
		}
	else
	{
		DWORD error = GetLastError();
		LogInstance.WriteLog(const_cast<LPTSTR>(_T("CreateThread failed: %d")),error);
		return error;
	}
}
fd_set readfds;
DWORD MyWinDivert::ReceiveCallback(LPVOID prc) {

					//handle connection and packets
	int max_sd, activity;
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
				LogInstance.WriteLog(const_cast<LPTSTR>(_T("select failed: %d")), error);
				exit(-1);
			}
			if (FD_ISSET(main_socket, &readfds))
			{
				int addrlen = sizeof(address);
				new_socket = accept(main_socket, (struct sockaddr*)&address, &addrlen);
				if (new_socket == INVALID_SOCKET)
				{
					int error = WSAGetLastError();
					LogInstance.WriteLog(const_cast<LPTSTR>(_T("Socket in thread failed: %d")), error);
					exit(-1);
				}
				LogInstance.WriteLog(const_cast<LPTSTR>(_T("Module connected")));
			}
			Sleep(100);
		}
		
		{
			std::vector<unsigned char> getsize;
			getsize.resize(4);
			if(getBytes(getsize, 4) == false) continue;
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
