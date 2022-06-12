#pragma once
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"

#pragma pack(push, 1)

typedef struct _SWPACKETOBJECTCREATE {
	BYTE _unknown01;
	/*UINT32 _id;
	FLOAT _locationX;
	FLOAT _locationY;
	FLOAT _locationZ;
	FLOAT _unknownFloat1;
	FLOAT _unknownFloat2;
	FLOAT _unknownFloat3;
#ifdef SERVER_KOREA
	BYTE _unknown02[17];
#endif
#ifdef SERVER_STEAM
	BYTE _unknown02[17]; // unknown01 -> id -> unknown02 구조인채로 33
#endif
#ifdef SERVER_JAPAN
	BYTE _unknown02[17]; // same as KR server
#endif
	UINT32 _realDB2;
	UINT32 _owner_id;
	BYTE _unknown03[54];
	UINT32 _db2;*/
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
}SWPACKETOBJECTCREATE;

#pragma pack(pop)

class SWPacketObjectCreate : public SWPacket {
protected:
	SWPacketObjectCreate() {}

public:
	SWPacketObjectCreate(SWHEADER* swheader, BYTE* data);
	~SWPacketObjectCreate() {}

	VOID Do();
	VOID Log();
	VOID Debug();
};