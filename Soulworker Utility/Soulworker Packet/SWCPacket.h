#pragma once
#define SWCONSTVALUE 1

#pragma pack(push, 1)

typedef struct _SWCHEADER {
	USHORT _magic;
	USHORT _size;
	UCHAR _const_value01; //1 for recv 2 for sent, so sent packets dont crash on recv
	UCHAR unknownshit1;
	USHORT _op;
	UCHAR unknownshit2;
} SWCHEADER;

#pragma pack(pop)

class SWCPacket : public MemoryPool<SWCPacket, 10> {
protected:
	SWCHEADER* _swheader;
	BYTE* _data;

	SWCPacket() {}
	SWCPacket(SWCPacket& other) {}

public:
	SWCPacket(SWCHEADER* swheader, BYTE* data);
	virtual ~SWCPacket() {}

	virtual VOID Debug();
	virtual VOID Log();
	virtual VOID Do();
};