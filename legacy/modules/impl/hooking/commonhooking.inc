#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_impl_commonhooking
	#endinput
#endif
#define _attdef_impl_commonhooking

/*
	Hooking some common functions
*/

//defining an abbreviation to avoid method name truncation while generating y_hooks
#include <YSI_Coding\y_hooks>

#define TogglePlayerCtrlable TogglePlayerControllable
// Add "Frozen" variable to this function and fix parachute bug
hook native TogglePlayerCtrlable(playerid, toggle)
{
	if (!toggle)
	{
		if (GetPlayerWeapon(playerid) == WEAPON_PARACHUTE)
			Player[playerid][HadParachuteBeforeFreeze] = true;
	}
	else
	{
		if (Player[playerid][HadParachuteBeforeFreeze])
		{
			GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 9999);
			Player[playerid][HadParachuteBeforeFreeze] = false;
		}
	}

	return continue(playerid, toggle);
}

// Hook SetPlayerSkin to fix crashes
hook native SetPlayerSkin(playerid, skinid)
{
	if (GetPlayerSkin(playerid) == skinid)
		return 1;
	if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		return 1;
	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: r;
		new isControllable = IsPlayerControllable(playerid);
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, r);
		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, r);
		TogglePlayerControllable(playerid, isControllable);
		return continue(playerid, skinid);
	}
	if (IsPlayerInAnyVehicle(playerid))
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: r;
		new isControllable = IsPlayerControllable(playerid);
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, r);
		new vehicleid = GetPlayerVehicleID(playerid);
		new seatid	  = GetPlayerVehicleSeat(playerid);
		RemovePlayerFromVehicle(playerid);
		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, r);
		TogglePlayerControllable(playerid, isControllable);
		new ret = continue(playerid, skinid);
		PutPlayerInVehicle(playerid, vehicleid, seatid);
		return ret;
	}
	return continue(playerid, skinid);
}

// Hook SpawnPlayer to fix spawning player when in vehicle
hook native SpawnPlayer(playerid)
{
	TogglePlayerSpectating(playerid, false);
	if (IsPlayerInAnyVehicle(playerid))
		SetPlayerPos(playerid, 0.0, 0.0, 0.0);
	return continue(playerid);
}

#if defined _YSF_included
// Hook GetPlayerWeaponData to fix a bug: "old weapons with no ammo left are still returned"
hook native GetPlayerWeaponData(playerid, slot, &weapons, &ammo)
{
	// This reuses the "slot" variable so we don't have to declare a new one
	// and can put all the code in a single statement.
	return
		slot = continue(playerid, slot, weapons, ammo),
		weapons = ammo ? weapons : 0,
		slot;
}
#endif
