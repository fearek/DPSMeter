#include "pch.h"
#include ".\Soulworker Packet\SWPacketMazeStart.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketMazeStart::SWPacketMazeStart(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketMazeStart::Do() {
	DAMAGEMETER.SetMazeState(FALSE);
}

VOID SWPacketMazeStart::Log() {

}

VOID SWPacketMazeStart::Debug() {
	//LogInstance.WriteLog(const_cast<LPTSTR>(_T("[TEST] [MAZE START]")));

	LogInstance.MyLog(_T("Maze Start\n"));
	for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
		LogInstance.MyLog(_T("%02x "), _data[i]);
	LogInstance.MyLog(_T("\n"));
}