#pragma once
#include ".\Language\Region.h"
#include ".\Soulworker Packet\PacketType.h"
#include ".\Soulworker Packet\SWPacket.h"

#define SWSPACKETMAKER SWSPacketMaker::getInstance()

#define KEY_FILE_NAME "SWPkey.bin"

#define NO_SEGMENTATION 0
#define YES_SEGMENTATION 1
#define REASSAMBLY 2
#define NO_SWHEADER 3
#define NO_SWDATA 4
#define SEGMENTATION_SUCCESS 5
#define SEGMENTATION_FAILED 6

#define DEBUG_SEGMENTATION 0
#define DEBUG_CREATESPACKET 0
#define DEBUG_RESIZEPACKET 0

class SWSPacketMaker : public Singleton<SWSPacketMaker> {
private:
	class SegmentationPacket {
	private:
		BYTE* _data;
		SIZE_T _size;

		SIZE_T _curSize;
		SIZE_T _packetSize;

		IPv4Packet _packet;

	public:
		SegmentationPacket() {
			_data = nullptr;
			_size = 0;
			_curSize = 0;
			_packetSize = 0;
		}

		~SegmentationPacket() {

			if (_data != nullptr)
				delete[] _data;

			_data = nullptr;
		}

		VOID Init(SIZE_T size) {

			if (_data == nullptr) {
				_data = new BYTE[size];
				_size = size;
			}

			if (_size < size) {
				delete[] _data;
				_data = new BYTE[size];
				_size = size;
			}

			_curSize = 0;
			_packetSize = size;

#if DEBUG_SEGMENTATION == 1
			Log::WriteLogA(const_cast<CHAR*>("[segmentationPacket Init] [curSize = %d] [packetSize = %d]"), _curSize, _packetSize);
#endif

		}

		SIZE_T GetRemainSize() {
#if DEBUG_SEGMENTATION == 1
			Log::WriteLogA(const_cast<CHAR*>("[segmentationPacket RemainSize = %d]"), _packetSize - _curSize);
#endif

			return _packetSize - _curSize;
		}

		DWORD AppendData(BYTE* data, SIZE_T size) {

			memcpy(_data + _curSize, data, size);

			int temp_debug = _curSize;
			_curSize += size;

#if DEBUG_SEGMENTATION == 1
			Log::WriteLogA(const_cast<CHAR*>("[segmentationPacket AppendData Before curSize = %d After curSize = %d]"), temp_debug, _curSize);

			for (int i = temp_debug; i < _curSize; i++)
				printf("%02x ", _data[i]);
			printf("\n");
#endif

			if (_curSize == _packetSize)
				return SEGMENTATION_SUCCESS;
			else if (_curSize < _packetSize)
				return SEGMENTATION_FAILED;
		}

		IPv4Packet* GetData() {
			_packet._data = _data;
			_packet._datalength = _packetSize;

			return &_packet;
		}
	};


	VOID Decrypt(BYTE* data, const UINT size, const UINT start);

#if defined(SERVER_KOREA)
	BYTE _keyTable[64] = { 0xee, 0x1b, 0xde, 0xa6, 0x46, 0xe9, 0x2a, 0xdb, 0x97, 0x67, 0x9c, 0x02, 0x3c, 0xce, 0x9a };
	char _keyInfo[32] = "No_key_info";
	int _keyLength = 15;

	USHORT _SWMAGIC = 3;
#endif
#if defined(SERVER_STEAM)
	BYTE _keyTable[64] = { 0x14, 0xb2, 0x99, 0x12, 0xcc, 0x23, 0xb9, 0x90, 0xf3, 0x08, 0x3d, 0xae, 0xe0, 0xac, 0x51 };
	char _keyInfo[32] = "No_key_info";
	int _keyLength = 15;

	USHORT _SWMAGIC = 3;
#endif
#if defined(SERVER_JAPAN) // same as past of KR server
	BYTE _keyTable[64] = { 0x60, 0x3B, 0x0B };
	char _keyInfo[32] = "No_key_info";
	int _keyLength = 3;

	USHORT _SWMAGIC = 2;
#endif


	SWSHEADER* GetSWSHeader(IPv4Packet* packet);
	BYTE* GetSWData(IPv4Packet* packet);

	VOID ResizePacket(IPv4Packet* packet);
	VOID ResizePacket(SIZE_T remainsize, IPv4Packet* packet);

	DWORD CheckSegmentation(IPv4Packet* packet);
	BOOL _isSegmentation;

	VOID StartReassambly(IPv4Packet* packet);
	VOID Reassambly(IPv4Packet* packet);
	SegmentationPacket _segmentationPacket;

	VOID CreateSWPacket(IPv4Packet* packet);

	VOID CheckRemainPacket(IPv4Packet* packet);

public:
	SWSPacketMaker();
	~SWSPacketMaker();

	DWORD Parse(IPv4Packet* packet);
};