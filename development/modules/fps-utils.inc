#if defined _FPS_utils_included
	#endinput
#endif
#define _FPS_utils_included

#include <YSI_Coding\y_hooks>

static const FPS_UPDATE_SYNC		 = 205;

static s_FPS[MAX_PLAYERS]			 = { 0, ... };
static s_LastDrunkLevel[MAX_PLAYERS] = { 0, ... };

hook OnPlayerConnect(playerid)
{
	s_FPS[playerid]			   = 0;
	s_LastDrunkLevel[playerid] = 0;
	return 1;
}

stock GetPlayerFPS(playerid) { return s_FPS[playerid]; }

IPacket:FPS_UPDATE_SYNC(playerid, BitStream:bs)
{
	static currentDrunkLevel;

	BS_SetReadOffset(bs, 8 + 32);
	BS_ReadInt32(bs, currentDrunkLevel);

	s_FPS[playerid]			   = max(s_LastDrunkLevel[playerid] - currentDrunkLevel - 1, 0);
	s_LastDrunkLevel[playerid] = currentDrunkLevel;

	if (currentDrunkLevel <= 750)
	{
		new pingBasedCompensation = s_FPS[playerid] * GetPlayerPing(playerid) / 1000;
		SetPlayerDrunkLevel(playerid, currentDrunkLevel + 1250 - pingBasedCompensation);
		s_LastDrunkLevel[playerid] += 1250;
	}
	// not using this function is sub optimal, but there's not much of a choice with this gamemode
	// fps, ping and pl textdraws are tied together, i'll let this be updated by a timer instead
	//CallLocalFunction(#OnFPSUpdate, #ii, playerid, s_FPS[playerid]);
	return 1;
}
