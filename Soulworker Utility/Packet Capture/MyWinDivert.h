#pragma once

#define WINDIVERT MyWinDivert::getInstance()


#define DEBUG_DIVERT_ALL 0
#define DEBUG_DIVERT_IP 0
#define DEBUG_DIVERT_TCP 0
#define DEBUG_DIVERT_DATA 0

class MyWinDivert : public Singleton<MyWinDivert> {
private:
	static DWORD WINAPI ReceiveCallback(LPVOID prc);

	HANDLE _handle;

public:
	MyWinDivert() { }
	~MyWinDivert() {}

	DWORD Init();
};