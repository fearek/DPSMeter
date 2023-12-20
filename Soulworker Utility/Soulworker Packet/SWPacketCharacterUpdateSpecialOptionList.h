#pragma once
#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"

#pragma pack(push, 1)
typedef struct _SWPacketCharacterUpdateSpecialOptionListHeader {

	uint32_t _playerID;
	uint8_t _listCount;

}SWPacketCharacterUpdateSpecialOptionListHeader;

typedef struct _SWPacketCharacterUpdateSpecialOptionVal {

	uint16_t _listID;
	float _listVal;

}SWPacketCharacterUpdateSpecialOptionVal;
#pragma pack(pop)

class SWPacketCharacterUpdateSpecialOptionList : public SWPacket {
protected:
	SWPacketCharacterUpdateSpecialOptionList() {}

public:
	SWPacketCharacterUpdateSpecialOptionList(SWHEADER* swheader, uint8_t* data);
	~SWPacketCharacterUpdateSpecialOptionList() {}

	void Do();
	void Log();
	void Debug();
};