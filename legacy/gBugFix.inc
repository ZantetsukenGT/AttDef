#if defined _gBugFix_included
	#endinput
#endif
#define _gBugFix_included

/*
This include prevents the bug where if you press G to enter a vehicle as a passenger and after 3 seconds entry isn't achieved you are teleported inside.
This is abusable as a player may start to enter an enemy player's vehicle, the enemy may drive off leaving the passenger still running after the car but
he will be teleported inside.
*/

#include <YSI_Coding\y_hooks>

static Float: s_PosX[MAX_PLAYERS];
static Float: s_PosY[MAX_PLAYERS];
static Float: s_PosZ[MAX_PLAYERS];
static s_LastAnimIndex[MAX_PLAYERS];
static bool: s_IsEntering[MAX_PLAYERS];

/**
	Specialized strfind for these exact strings.
	The strings were extracted from the passenger entry animation names from the game's default 211 vehicles
*/
static bool: GBUG_IsAcceptableAnimation(const animName[5])
{
	if (animName[0] == 'B')
	{
		if (animName[1] == 'I') return true; // biked, bikeh, bikes, bikev
		if (animName[1] == 'F') return true; // bf
		if (animName[1] == 'U' && animName[2] == 'S') return true; // bus
		return false;
	}
	if(animName[0] == 'C')
	{
		if (animName[1] == 'A' && animName[2] == 'R' && animName[3] == '_') return true; // car
		if (animName[1] == 'O' && animName[2] == 'A') return true; // coach
		return false;
	}
	if(animName[0] == 'T' && animName[1] == 'R' && animName[2] == 'U') return true; // truck
	if(animName[0] == 'V' && animName[1] == 'A') return true; // van
	if(animName[0] == 'Q') return true; // quad
	if(animName[0] == 'W' && animName[1] == 'F') return true; //WF
	return false;
}

hook native PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	s_IsEntering[playerid] = false;
	return continue(playerid, vehicleid, seatid);
}

hook OnPlayerConnect(playerid)
{
	s_IsEntering[playerid] = false;
	s_LastAnimIndex[playerid] = 0;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if ((s_IsEntering[playerid] = bool: ispassenger))
	{
		GetPlayerPos(playerid, s_PosX[playerid], s_PosY[playerid], s_PosZ[playerid]);
		//SendClientMessage(playerid, -1, "Attempting to enter vehicle as passenger..");
	}
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_PASSENGER && s_IsEntering[playerid]) // Can only be true from attempting normally
	{
		static animLib[1], animName[5];
		GetAnimationName(s_LastAnimIndex[playerid], animLib, sizeof(animLib), animName, sizeof(animName));
		if (!GBUG_IsAcceptableAnimation(animName))
		{
			SetPlayerPos(playerid, s_PosX[playerid], s_PosY[playerid], s_PosZ[playerid]);
			GameTextForPlayer(playerid, "~R~entry denied", 3000, 3);
		}
		s_IsEntering[playerid] = false;
	}
}

hook OnPlayerUpdate(playerid)
{
	static index;
	index = GetPlayerAnimationIndex(playerid);
	if (index != s_LastAnimIndex[playerid])
		s_LastAnimIndex[playerid] = index;
}
