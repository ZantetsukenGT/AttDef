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

static const BF_GETIN_LHS = 53;
static const BF_GETIN_RHS = 54;
static const SPRINT_CIVI = 1246;

static Float: s_PosX[MAX_PLAYERS];
static Float: s_PosY[MAX_PLAYERS];
static Float: s_PosZ[MAX_PLAYERS];
static bool: s_IsEntering[MAX_PLAYERS]	  = { false, ... };
static bool: s_ForceEntering[MAX_PLAYERS] = { false, ... };
static s_AnimQ1[MAX_PLAYERS]			  = { 0, ... };
static s_AnimQ2[MAX_PLAYERS]			  = { 0, ... };

hook native PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	SendClientMessage(playerid, -1, "PutPlayerInVehicle");
	s_IsEntering[playerid]	  = true;
	s_ForceEntering[playerid] = true;
	continue(playerid, vehicleid, seatid);
}

hook OnPlayerConnect(playerid)
{
	SendClientMessage(playerid, -1, "OnPlayerConnect");
	s_IsEntering[playerid]	  = false;
	s_ForceEntering[playerid] = false;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if ((s_IsEntering[playerid] = bool: ispassenger))
	{
		SendClientMessage(playerid, -1, "OnPlayerEnterVehicle attempt for passenger");
		s_ForceEntering[playerid] = false;
		GetPlayerPos(playerid, s_PosX[playerid], s_PosY[playerid], s_PosZ[playerid]);
		//SendClientMessage(playerid, -1, "Starting to enter vehicle..");
	}
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_PASSENGER) // Entered vehicle
	{
		SendClientMessage(playerid, -1, "OnPlayerStateChange passenger");
		if (!s_IsEntering[playerid])
		{
			SendClientMessage(playerid, -1, "OnPlayerStateChange passenger denied");
			SetPlayerPos(playerid, s_PosX[playerid], s_PosY[playerid], s_PosZ[playerid]);
			GameTextForPlayer(playerid, "~R~entry denied", 3000, 3);
		}
		s_IsTryingToEnter[playerid] = false;
		s_IsEntering[playerid]		= false;
	}
}

hook OnPlayerUpdate(playerid)
{
	if (!s_IsEntering[playerid])
		return SendClientMessage(playerid, -1, "OnPlayerUpdate: not trying");
	if ((s_IsEntering[playerid] = GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_ENTER_VEHICLE))
		return SendClientMessage(playerid, -1, "OnPlayerUpdate: actually entering");
	if (GetTickCount() - s_IsTryingToEnterTick[playerid] > 321)
	{
		SendClientMessage(playerid, -1, "OnPlayerUpdate: cancelled after 321 ms");
		s_IsTryingToEnter[playerid] = false; //player intentionally cancelled entrance to vehicle
	}
	SendClientMessage(playerid, -1, "OnPlayerUpdate: not entered within 321 ms but still trying");
	return 1;
}
