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

static bool: s_Controllable[MAX_PLAYERS] = { true, ... };

hook OnPlayerConnect(playerid)
{
	s_Controllable[playerid] = true;
	return 1;
}

stock bool: IsPlayerControllable(playerid) { return s_Controllable[playerid]; }

#define TogglePlayerCtrlable TogglePlayerControllable
// Add "Frozen" variable to this function and fix parachute bug
hook stock TogglePlayerCtrlable(playerid, toggle)
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
	s_Controllable[playerid] = !!toggle;
	return continue(playerid, toggle);
}

// Hook SetPlayerSkin to fix crashes
hook stock SetPlayerSkin(playerid, skinid)
{
	if (GetPlayerSkin(playerid) == skinid)
		return 1;
	if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		return 1;

	// Set spectators to re-spectate
	if (Player[playerid][BeingSpeced])
		SetTimerEx("ForceRespectate", 1000, false, "i", playerid);

	// Store info before re-spawn
	new Float: x,
		Float: y,
		Float: z,
		Float: r,
		currentWeapon = GetPlayerWeapon(playerid);
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, r);

	// Fixes vehicle bug
	if (IsPlayerInAnyVehicle(playerid))
		SetPlayerPos(playerid, x, y, z + 2);

	new currentWeapons[13][2];
	for (new i = 0; i < 13; i++) GetPlayerWeaponData(playerid, i, currentWeapons[i][0], currentWeapons[i][1]);

	// Set spawn info and spawn player
	SetSpawnInfo(playerid, GetPlayerTeam(playerid), skinid, x, y, z - 0.4, r, 0, 0, 0, 0, 0, 0);
	Player[playerid][IgnoreSpawn] = true;
	SpawnPlayer(playerid);

	// Set info back after re-spawn
	SetHP(playerid, Player[playerid][pHealth]);
	SetAP(playerid, Player[playerid][pArmour]);
	SetPlayerInterior(playerid, GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(playerid));

	for (new i = 0; i < 13; i++) GivePlayerWeapon(playerid, currentWeapons[i][0], currentWeapons[i][1]);
	SetPlayerArmedWeapon(playerid, currentWeapon);
	return continue(playerid, skinid);
}

// Hook SpawnPlayer to fix spawning player when in vehicle
hook stock SpawnPlayer(playerid)
{
	if (GetPlayerVehicleID(playerid))
		SetPlayerPos(playerid, 0.0, 0.0, 0.0);
	return continue(playerid);
}

// Hook GetPlayerWeaponData to fix a bug: "old weapons with no ammo left are still returned"
hook stock GetPlayerWeaponData(playerid, slot, &weapons, &ammo)
{
	// This reuses the "slot" variable so we don't have to declare a new one
	// and can put all the code in a single statement.
	return slot = continue(playerid, slot, weapons, ammo), weapons = ammo ? weapons : 0, slot;
}
