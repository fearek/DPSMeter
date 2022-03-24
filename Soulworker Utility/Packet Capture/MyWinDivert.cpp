#include "pch.h"
#include ".\Packet Capture\MyWinDivert.h"
#include ".\Soulworker Packet\SWPacketMaker.h"
#include ".\Soulworker Packet\SWSPacketMaker.h"

DWORD MyWinDivert::Init() {

	DWORD error = ERROR_SUCCESS;

	//init connection

		CreateThread(NULL, 0, ReceiveCallback, this, 0, NULL);


	return error;
}

DWORD MyWinDivert::ReceiveCallback(LPVOID prc) {
					//handle connection and packets
					//SWSPACKETMAKER.Parse(&packet);
	while (true)
	{
		;
	}
	return 0;
}

VOID MyWinDivert::PrintIPHeader(IPv4Packet* p_packet) {

	if (p_packet == nullptr)
		return;

	IPHEADER* ih = p_packet->_ipHeader;

	printf("======== IP Header ========\n");
	printf("Version : %d\n", ih->version);
	printf("len : %d\n", ih->len * 4);
	printf("length : %d\n", ih->length);
	printf("TTL : %d\n", ih->ttl);
	printf("protocol : %d\n", ih->protocol);
	printf("Src IP  : %d.%d.%d.%d\n", ih->src_ip & 0xFF, (ih->src_ip >> 8) & 0xFF, (ih->src_ip >> 16) & 0xF, (ih->src_ip >> 24) & 0xFF);
	printf("Dst IP  : %d.%d.%d.%d\n", ih->dest_ip & 0xFF, (ih->dest_ip >> 8) & 0xFF, (ih->dest_ip >> 16) & 0xF, (ih->dest_ip >> 24) & 0xFF);

	return;
}

VOID MyWinDivert::PrintTCPHeader(IPv4Packet* p_packet) {

	if (p_packet == nullptr)
		return;

	TCPHEADER* th = p_packet->_tcpHeader;

	printf("======== TCP Header ========\n");
	printf("src_port : %u\n", _byteswap_ushort(th->src_port));
	printf("dest_port : %u\n", _byteswap_ushort(th->dest_port));
	printf("length : %d\n", th->length * 4);
}