#pragma once
#include ".\Soulworker Packet\SWPacket.h"
/* 0x01 */
#include ".\Soulworker Packet\SWPacketHeartbeat.h"

/* 0x03 */
#include ".\Soulworker Packet\SWPacketStatChange.h"
#include ".\Soulworker Packet\SWPacketSpecialStatChange.h"
#include ".\Soulworker Packet\SWPacketDead.h"
/* 0x04 */
#include ".\Soulworker Packet\SWPacketWorldChange.h"
#include ".\Soulworker Packet\SWPacketMazeStart.h"
#include ".\Soulworker Packet\SWPacketSpawnedCharInfo.h"
#include ".\Soulworker Packet\SWPacketObjectCreate.h"
#include ".\Soulworker Packet\SWPacketMonsterInfo.h"
/* 0x05 */
#include ".\Soulworker Packet\SWPacketStartMove.h"
// stopMove
// jump
// cancelwithmove

/* 0x06 */
// DODGE
#include ".\Soulworker Packet\SWPacketUseSkill.h"
#include ".\Soulworker Packet\SWPacketOtherUseSkill.h"
#include ".\Soulworker Packet\SWPacketDamage.h"
#include ".\Soulworker Packet\SWPacketBuffIn.h"
#include ".\Soulworker Packet\SWPacketBuffOut.h"
// projectile
#include ".\Soulworker Packet\SWPacketAkasic.h"
#include ".\Soulworker Packet\SWPacketCooldown.h"


/* 0x07 */
#include ".\Soulworker Packet\SWPacketChat.h"
// chat_whisper

/* 0x11 */
#include ".\Soulworker Packet\SWPacketMazeEnd.h"

/* 0x12 */
#include ".\Soulworker Packet\SWPacketParty.h"
#include ".\Soulworker Packet\SWPacketPartyListInfo.h"

/* 0x17 ?? */
#include ".\Soulworker Packet\SWPacketMonsterKilled.h"
#include ".\Soulworker Packet\SWPacketAggroChanged.h"
#include ".\Soulworker Packet\SWPacketMonsterStatUpdate.h"
/* 0x23 Gesture */
#include ".\Soulworker Packet\SWPacketGestureUsed.h"

/* 0x2e */
#include ".\Soulworker Packet\SWPacketPos.h"

// SWSPacket
#include ".\Soulworker Packet\SWSPacket.h"
#include ".\Soulworker Packet\SWSPacketMySkillUsed.h"
#include ".\Soulworker Packet\SWSPacketMyDodgeUsed.h"

// SWCPacket
#include ".\Soulworker Packet\SWCPacket.h"
#include ".\Soulworker Packet\SWCPing.h"
#include ".\Soulworker Packet\SWCPresence.h"
// 대충 여기에 다 집어놓고 packetType만 include해서 쓰면 됨



enum OPcode {
	HEARTBEAT = 0x0106,
	SPECIALSTATCHANGE = 0x0347,
	STATCHANGE = 0x0334,
	DEAD = 0x0341,

	WORLDCHANGE = 0x0402,
	MAZESTART = 0x0408,
	SPAWNED_CHARINFO = 0x0411,
	OBJECTCREATE = 0x0415,	
	MONSTER_INFO = 0x0423,
	STARTMOVE = 0x0502,
	STOPMOVE = 0x0504,
	JUMP = 0x0506,
	CANCEL_WITHMOVE = 0x0511,
 
	DODGE = 0x0607, // 회피,다운후구르기, 공중피격후 회피에 사용됨?
	USESKILL = 0x0609,
	OTHER_USESKILL = 0x0610,
	DAMAGE = 0x0613,
	BUFFIN = 0x0614,
	BUFFOUT = 0x0615,
	PROJECTILE = 0x0632,
	AKASIC = 0x067b,
	COOLDOWN = 0x067c,

	CHAT = 0x0701,
	CHAT_WHISPER = 0x0702,

	MAZEEND = 0x1175,

	/* 0x12 Party*/
	PARTY = 0x1209,
	PARTY_LIST_INFO = 0x1236,

	MONSTER_KILLED = 0x1711,
	MONSTER_STAT_UPDATE = 0x1712,
	AGGRO_CHANGED = 0x1722,

	GESTURE_USED = 0x2301,

	POS = 0x2e09,
};