#if defined opws_fix_included_
	#endinput
#endif
#define opws_fix_included_

// Credits to Boorz for the original include

#include <Pawn.RakNet>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_hooks>

timer DeferredOnScriptInit[0]()
{
	SetServerRule("lagcomp", "Off");
	return 1;
}

hook OnScriptInit()
{
	defer DeferredOnScriptInit();
	return 1;
}

// skips: 11 boolean bits, 2 int8, 1 int16, 3 floats, 7 ints32
static const LAGCOMP_WRITE_OFFSET = 11 * 1 + 2 * 8 + 1 * 16 + 3 * 32 + 7 * 32;
static const INITGAME_ORPC		  = 139;
ORPC:INITGAME_ORPC(playerid, BitStream: bs)
{
	new originalWO;
	PR_SendRPC(bs, playerid, INITGAME_ORPC, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);

	BS_GetWriteOffset(bs, originalWO);
	BS_SetWriteOffset(bs, LAGCOMP_WRITE_OFFSET);

	BS_WriteValue(bs, PR_UINT8, 0);

	BS_SetWriteOffset(bs, originalWO);

	PR_SendRPC(bs, playerid, INITGAME_ORPC, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);
	CallLocalFunction(#GOOD_OnPlayerConnect, #i, playerid);
	return 0;
}

static const BULLET_SYNC = 206;
IPacket:BULLET_SYNC(playerid, BitStream: bs)
{
	new bData[PR_BulletSync];
	BS_SetReadOffset(bs, 8);
	BS_ReadBulletSync(bs, bData);

	bData[PR_hitType]	 = BULLET_HIT_TYPE_NONE;
	bData[PR_hitId]		 = 0xFFFF;

	// set offsets to whatever hitPos is for `BULLET_HIT_TYPE_NONE` to work
	new Float: fPosX	 = bData[PR_hitPos][0];
	new Float: fPosY	 = bData[PR_hitPos][1];
	new Float: fPosZ	 = bData[PR_hitPos][2];
	bData[PR_offsets][0] = fPosX;
	bData[PR_offsets][1] = fPosY;
	bData[PR_offsets][2] = fPosZ;

	BS_SetWriteOffset(bs, 8);
	BS_WriteBulletSync(bs, bData);
	return 1;
}
