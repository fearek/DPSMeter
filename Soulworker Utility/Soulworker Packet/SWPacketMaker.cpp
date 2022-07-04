#include "pch.h"
#include ".\Soulworker Packet\PacketType.h"
#include ".\Soulworker Packet\SWPacketMaker.h"


SWPacketMaker::SWPacketMaker() {
	//_isSegmentation = FALSE;

}

SWPacketMaker::~SWPacketMaker() {

}

SWHEADER* SWPacketMaker::GetSWHeader(std::vector<unsigned char>& packet) {

	if (packet.size() < sizeof(SWHEADER)) {
		return nullptr;
	}
		

	SWHEADER* swheader = (SWHEADER*)(&packet[0]);
	//if (swheader->_magic != _SWMAGIC || (swheader->_const_value01 != 1 && swheader->_const_value01 != 2 )) {
	//	return nullptr;
	//}
	if (swheader->_const_value01 != 1 && swheader->_const_value01 != 2 && swheader->_const_value01 != 3)
	{
		return nullptr;
	}
	return swheader;

}

BYTE* SWPacketMaker::GetSWData(std::vector<unsigned char>& packet) {

	return (BYTE*)(&packet[0]);
}



VOID SWPacketMaker::CreateSWPacket(std::vector<unsigned char>& packet) {
	//packethandler
	SWHEADER* swheader = GetSWHeader(packet);
	BYTE* data = GetSWData(packet);
	if (swheader == nullptr) {
		return;
	}
	if (data == nullptr)
	{
		return;
	}

	//Decrypt(data, swheader->_size - sizeof(SWHEADER) + 2, sizeof(SWHEADER) - 2);

	SWPacket* swpacket = nullptr;
	DAMAGEMETER.GetLock();
	{
		if (swheader->_const_value01 == 1) {
			switch (_byteswap_ushort(swheader->_op)) {

				/* 0x01*/
		//	case OPcode::HEARTBEAT:
				//swpacket = new SWPacketHeartbeat(swheader, data);
			//	break;

				/*0x03*/
			case OPcode::SPECIALSTATCHANGE:
				swpacket = new SWPacketSpecialStatChange(swheader,data);
				break;

			case OPcode::STATCHANGE:
				swpacket = new SWPacketStatChange(swheader, data);
				break;
			case OPcode::DEAD:
				swpacket = new SWPacketDead(swheader, data);
				break;

				/*0x04*/
			case OPcode::WORLDCHANGE:
				swpacket = new SWPacketWorldChange(swheader, data);
				break;
			case OPcode::MAZESTART:
				swpacket = new SWPacketMazeStart(swheader, data);
				break;
			case OPcode::SPAWNED_CHARINFO:
				swpacket = new SWPacketSpawnedCharInfo(swheader, data);
				break;
			case OPcode::OBJECTCREATE:
				swpacket = new SWPacketObjectCreate(swheader, data);
				break;
			case OPcode::MONSTER_INFO:
				swpacket = new SWPacketMonsterInfo(swheader,data);
				break;
				/*0x05 these aint used so why are they here lol */
			//case OPcode::STARTMOVE:
			//	swpacket = new SWPacketStartMove(swheader, data);
			//	break;
			//case OPcode::STOPMOVE:
			//	break;
			//case OPcode::JUMP:
			//	break;
			//case OPcode::CANCEL_WITHMOVE:
			//	break;

				/*0x06 Combat*/
			//case OPcode::EVADE:
			//	break;
			case OPcode::USESKILL:
				swpacket = new SWPacketUseSkill(swheader, data);
				break;
			case OPcode::OTHER_USESKILL:
				swpacket = new SWPacketOtherUseSkill(swheader, data);
				break;
			case OPcode::DAMAGE:
				swpacket = new SWPacketDamage(swheader, data);
				break;
			case OPcode::BUFFIN:
				swpacket = new SWPacketBuffIn(swheader, data);
				break;
			case OPcode::BUFFOUT:
				swpacket = new SWPacketBuffOut(swheader, data);
				break;
				//case OPcode::PROJECTILE:
				//	break;
			case OPcode::AKASIC:
				swpacket = new SWPacketAkasic(swheader, data);
				break;
			case OPcode::COOLDOWN:
				swpacket = new SWPacketCooldown(swheader, data);
				break;

				/*0x07*/
			//case OPcode::CHAT: //why is this here too, not used
			//	swpacket = new SWPacketChat(swheader, data);
			//	break;

				/* 0x11 */

			case OPcode::MAZEEND:
				swpacket = new SWPacketMazeEnd(swheader, data);
				break;

				/* 0x12 Party */
			case OPcode::PARTY:
				swpacket = new SWPacketParty(swheader, data);
				break;
				//case OPcode::PARTY_LIST_INFO:
					//swpacket = new SWPacketPartyListInfo(swheader, data);
				//	break;

					/* 0x17 ?? */
			case OPcode::MONSTER_KILLED:
				swpacket = new SWPacketMonsterKilled(swheader, data);
				break;
			case OPcode::AGGRO_CHANGED:
				swpacket = new SWPacketAggroChanged(swheader, data);
				break;

				/* 0x23 Gesture*/ //again why is this here
			//case OPcode::GESTURE_USED:
				//swpacket = new SWPacketGestureUsed(swheader, data);
				//break;

				/* 0x2e Force*/
			case OPcode::POS:
				swpacket = new SWPacketPos(swheader, data);
				break;


			default:
				//swpacket = new SWPacket(swheader, data);
				break;
			}
		}
		else if (swheader->_const_value01 == 2)
		{
			switch (_byteswap_ushort(swheader->_op)) {
			case 0x0606:
				swpacket = new SWSPacketMyDodgeUsed(swheader, data);
				break;
			case 0x0608:
				swpacket = new SWSPacketMySkillUsed(swheader, data);
				break;
			}
		}
		else if (swheader->_const_value01 == 3)
		{
			switch (_byteswap_ushort(swheader->_op))
			{
			case 0x0101:
				swpacket = new SWCPing(swheader,data);
				break;
			case 0x0102:
				swpacket = new SWCPresence(swheader,data);
				break;
			}
		}
		else
		{
		DAMAGEMETER.FreeLock();
		return;
	}
		if (swpacket != nullptr) {
#if DEBUG_CREATEPACKET == 1 // && defined(_DEBUG)
			swpacket->Debug();
#endif
			// Todo
			swpacket->Do();

			delete swpacket;
		}
	}
	DAMAGEMETER.FreeLock();
	return;
	//ResizePacket(packet);
}

char* SWPacketMaker::GetKeyInfo() {
	return _keyInfo;

}