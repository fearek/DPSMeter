#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETMONSTERINFO {
	unsigned int _id;
	float _locationX;
	float _locationY;
	float _locationZ;
	float _unknownFloat1;
	float _unknownFloat2;
	float _unknownFloat3;
	unsigned char _unknown02[17];
	unsigned int _realDB2;
	unsigned int _owner_id;
	unsigned int spawnBoxID;
	unsigned int motionClass;
	unsigned char battlePos;
	float curSuperArmor;
	float maxSuperArmor;
	char bullshit[8];
	unsigned char statamount; //thats not all, the rest of the struct is read in cpp file
}SWPACKETMONSTERINFO;
typedef struct _SWPACKETSTATINFO {

	BYTE type;
	FLOAT val;

}SWPACKETMONSTERSTATINFO;
typedef struct _SWPACKETMONSTERINFOFOOTER {

	ULONG64 unk01;
	ULONG64 unk02;
	FLOAT unk03;
	BYTE unknownCount;

}SWPACKETMONSTERINFOFOOTER;
typedef struct _SWPACKETMONSTERINFOUNKNOWN {

	UINT32 unk01;
	FLOAT unk02;
	BYTE unk03;
	UINT32 unk04;
	BYTE unk05;

}SWPACKETMONSTERINFOUNKNOWN;
#pragma pack(pop)

class SWPacketMonsterInfo : public SWPacket {
protected:
	SWPacketMonsterInfo() {}

public:
	SWPacketMonsterInfo(SWHEADER* swheader, BYTE* data);
	~SWPacketMonsterInfo() {}

	VOID Do();
	VOID Log();
	VOID Debug();
};