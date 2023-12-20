#include "pch.h"
#include ".\Soulworker Packet\SWPacketMazeEnd.h"
#include ".\Damage Meter\Damage Meter.h"

SWPacketMazeEnd::SWPacketMazeEnd(SWHEADER* swheader, uint8_t* data) : SWPacket(swheader, data) {

}

void SWPacketMazeEnd::Do() 
{
	SWPACKETCHATMAZEEND* pMazeEnd = (SWPACKETCHATMAZEEND*)(_data + sizeof(SWHEADER));

	DAMAGEMETER.SetMazeState(true);
	DAMAGEMETER.Suspend();
	DAMAGEMETER.SetRealClearTime(pMazeEnd->_clearTime);
}

void SWPacketMazeEnd::Log() {

}

void SWPacketMazeEnd::Debug() {
	/*SWPACKETCHATMAZEEND* pMazeEnd = (SWPACKETCHATMAZEEND*)(_data + sizeof(SWHEADER));
	LogInstance.WriteLog("[SWPacketMazeEnd] rank = %d, playScore = %u, clearScore = %u, clearTime = %u",
		pMazeEnd->_rank, pMazeEnd->_playScore, pMazeEnd->_clearScore, pMazeEnd->_clearTime);*/
}