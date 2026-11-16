#if defined _gBugFix_included
	#endinput
#endif
#define _gBugFix_included

/*
This include prevents the bug where if you press G to enter a vehicle as a passenger and after 3 seconds entry isn't achieved you are teleported inside.
This is abusable as a player may start to enter an enemy player's vehicle, the enemy may drive off leaving the passenger still running after the car but
he will be teleported inside.
*/

#include <a_samp>
#include <YSI_Coding\y_hooks>

#if !defined PLAYER_STATE
	#define PLAYER_STATE: _:
#endif

static Float: s_PosX[MAX_PLAYERS];
static Float: s_PosY[MAX_PLAYERS];
static Float: s_PosZ[MAX_PLAYERS];
static s_LastAnimIndex[MAX_PLAYERS];
static bool: s_IsEnteringAsPassenger[MAX_PLAYERS];

// 1812 is the maximum index samp can return from GetPlayerAnimationIndex
#define GBUG_MAX_ANIMATIONS (1813)
static bool: s_IsAcceptableAnimation[GBUG_MAX_ANIMATIONS char] = { false, ... };

// Sets the range of animations that represent a valid passenger vehicle entry.
static GBUG_SetAcceptableRange(min, max)
{
	for (new i = min; i <= max; i++) s_IsAcceptableAnimation { i } = true;
}

// Returns whether the player is performing a passenger vehicle enter animation.
stock bool: GBUG_IsPerformingEntering(playerid) { return s_IsAcceptableAnimation { s_LastAnimIndex[playerid] }; }

hook OnScriptInit()
{
	// Sets the ranges as accepted animations from the default 211 samp vehicle passenger entry animations.
	GBUG_SetAcceptableRange(53, 56);	 // bf
	GBUG_SetAcceptableRange(57, 75);	 // biked
	GBUG_SetAcceptableRange(76, 93);	 // bikeh
	GBUG_SetAcceptableRange(103, 122);	 // bikes
	GBUG_SetAcceptableRange(123, 140);	 // bikev
	GBUG_SetAcceptableRange(225, 233);	 // bus
	GBUG_SetAcceptableRange(1007, 1060); // car_
	GBUG_SetAcceptableRange(354, 359);	 // coach
	GBUG_SetAcceptableRange(1626, 1642); // truck
	GBUG_SetAcceptableRange(1648, 1655); // van
	GBUG_SetAcceptableRange(1336, 1352); // quad
	GBUG_SetAcceptableRange(1666, 1683); // WF
	return 1;
}

// If a player is manually placed in a vehicle, allow it
hook native PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	s_IsEnteringAsPassenger[playerid] = false;
	return continue(playerid, vehicleid, seatid);
}

hook OnPlayerConnect(playerid)
{
	s_IsEnteringAsPassenger[playerid] = false;
	s_LastAnimIndex[playerid]		  = 0;
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	// Only save the player positions once he has pressed G
	if ((s_IsEnteringAsPassenger[playerid] = !!ispassenger))
	{
		GetPlayerPos(playerid, s_PosX[playerid], s_PosY[playerid], s_PosZ[playerid]);
	}
	return 1;
}

hook OnPlayerStateChange(playerid, PLAYER_STATE: newstate, PLAYER_STATE: oldstate)
{
	if (newstate == PLAYER_STATE_PASSENGER && s_IsEnteringAsPassenger[playerid]) // Can only be true from attempting normally
	{
		if (!GBUG_IsPerformingEntering(playerid))
		{
			SetPlayerPos(playerid, s_PosX[playerid], s_PosY[playerid], s_PosZ[playerid]);
			GameTextForPlayer(playerid, "~R~entry denied", 3000, 3);
		}
		s_IsEnteringAsPassenger[playerid] = false;
	}
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	s_LastAnimIndex[playerid] = GetPlayerAnimationIndex(playerid);
	return 1;
}
