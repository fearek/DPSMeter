#pragma once
#include <iostream>
#include <codecvt>
#include <locale>
#include <string>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

typedef std::chrono::system_clock::time_point timePoint;

#define FLOOR(x) (float)((int)x)

inline bool UTF16toUTF8(_In_ wchar_t* src, _Out_ char* dest, _In_ size_t destLen) {

	if (src == nullptr || dest == nullptr)
		return FALSE;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wchar_t_to_utf8;
	std::wstring wstr(src);
	std::string utf8str = wchar_t_to_utf8.to_bytes(wstr);

	if (destLen < utf8str.size())
		return FALSE;

	strcpy_s(dest, destLen, utf8str.c_str());

	return TRUE;
}

inline bool ANSItoUTF8(_In_ char* src, _Out_ char* dest, _In_ int32_t destLen) {

	if (src == nullptr || dest == nullptr)
		return FALSE;

	BSTR bstr;
	int len = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, NULL);
	bstr = SysAllocStringLen(NULL, len);

	MultiByteToWideChar(CP_UTF8, 0, src, -1, bstr, len);

	len = WideCharToMultiByte(CP_ACP, 0, bstr, -1, NULL, 0, NULL, NULL);

	if (len < 1)
		return FALSE;

	if (len < destLen) {
		WideCharToMultiByte(CP_ACP, 0, bstr, -1, dest, destLen, NULL, NULL);
	}
	else {
		SysFreeString(bstr);
		return FALSE;
	}

	return TRUE;
}

inline bool TextCommma(_In_ char* src, _Out_ char* dest) {

	if (src == nullptr || dest == nullptr) {
		return FALSE;
	}

	size_t len = strlen(src);

	while (*src) {
		*dest++ = *src++;

		if (--len && (len % 3) == 0)
			*dest++ = ',';
	}
	*dest++ = 0;

	return TRUE;
}

inline bool TextCommmaIncludeDecimal(_In_ double src, _In_ size_t destLen, _Out_ char* dest) 
{
	if (dest == nullptr) {
		return FALSE;
	}

	char tmp[128] = { 0 };
	char comma[128] = { 0 };
	double whole = floor(src);
	int decimal = int((src - whole) * 10) % 10;

	sprintf_s(tmp, "%.0f", whole);
	TextCommma(tmp, comma);
	sprintf_s(dest, destLen, "%s.%d", comma, decimal);

	return TRUE;
}

inline uint64_t GetCurrentTimeStamp() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static bool file_contents(const std::filesystem::path& path, std::string* str)
{
	if (!std::filesystem::is_regular_file(path))
		return FALSE;

	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file.is_open())
		return FALSE;

	std::string content{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

	file.close();

	*str = content;

	return TRUE;
}

#define MAX_BUFFER_LENGTH 1024

#pragma pack(push, 1)

typedef struct _ETHERNETHEADER {
	unsigned char DesMac[6];
	unsigned char SrcMac[6];
	unsigned short Type;
}ETHERNETHEADER;

typedef struct _IPHEADER {
	//little endian begin
	unsigned short len : 4;					//
	unsigned short version : 4;				//
	// little endian end
	unsigned short tos : 8;					// 
	unsigned short length;					// 
	unsigned short id;						// 16 
	//little endian begin
	unsigned short fragment_offset1 : 5;	// 
	unsigned short flags : 3;				// flag
	unsigned short fragment_offset2 : 8;	// 
	//little endian end
	unsigned short ttl : 8;					// ttl
	unsigned short protocol : 8;			// protocol tcp==06
	unsigned short checksum;				// 
	ULONG src_ip;					//  IP
	ULONG dest_ip;					//  IP
}IPHEADER;

typedef struct _TCPHEADER {
	unsigned short src_port;				//  port
	unsigned short dest_port;				//  port
	ULONG seq_number;				//  
	ULONG ack_number;				// ack 
	//little endian begin 18
	unsigned short reserved1 : 4;			// reserved
	unsigned short length : 4;				// 
	unsigned short fin : 1;					// FIN
	unsigned short syn : 1;					// SYN
	unsigned short rst : 1;					// RST
	unsigned short psh : 1;					// PSH
	unsigned short ack : 1;					// ACK
	unsigned short urg : 1;					// URG
	unsigned short reserved2 : 2;			// reserved
	//little endian end
	unsigned short window_size;				// 
	unsigned short tcp_checksum;			// TCP checksum
	unsigned short urg_point;				//
}TCPHEADER;

typedef struct _IPV4PACKET {
	ETHERNETHEADER* _ethernetHeader; // options
	IPHEADER* _ipHeader; // options
	TCPHEADER* _tcpHeader; // options
	const uint8_t* _pkt; // save packet origin ptr
	uint8_t* _data;
	size_t _datalength;
	bool _isRecv;
	uint64_t _ts;
}IPv4Packet;

#pragma pack(pop)