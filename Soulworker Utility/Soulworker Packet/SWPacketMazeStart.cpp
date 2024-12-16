#include "pch.h"
#include ".\Soulworker Packet\SWPacketMazeStart.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketMazeStart::SWPacketMazeStart(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

void SWPacketMazeStart::Do() {
	DAMAGEMETER.SetMazeState(FALSE);
}

void SWPacketMazeStart::Log() {

}

void SWPacketMazeStart::Debug() {
	//LogInstance.WriteLog("[TEST] [MAZE START]");

	//Log::MyLog("Maze Start\n");
	/*for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
		Log::MyLog("%02x ", _data[i]);
	Log::MyLog("\n");*/
}