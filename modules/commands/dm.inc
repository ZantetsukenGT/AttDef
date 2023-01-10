#if defined _attdef_cmd_dm
	#endinput
#endif
#define _attdef_cmd_dm

YCMD: dm(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "teleport you to a deathmatch arena.");
	new DMID;
	if (sscanf(params, "I(-1)", DMID) || DMID < 0)
		return SendUsageMessage(playerid, "/dm [DM ID]");
	if (Player[playerid][Playing])
		return 1;

	if (!Iter_Contains(CurrentDMs, DMID))
		return SendErrorMessage(playerid, "This DM does not exist.");

	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	ResetPlayerWeapons(playerid); // Reset all player weapons
	// Put player in a different virtual world so that if you create a DM in your lobby and you join the DM, you won't be able to see other players in the lobby.
	SetPlayerVirtualWorld(playerid, 1);
	SetHP(playerid, 100);
	SetAP(playerid, 100);

	Player[playerid][InDM]	  = true; // Keep a record of what is the player current status.
	Player[playerid][DMReadd] = DMID;
	Player[playerid][VWorld]  = 1;

	// format for SetPlayerSpawn(Playerid, Team, Skin, X, Y, X, Angle, Weapon 1, Weapon 1 Ammo, Weapon 2, Weapon 2 Ammo, Weapon 3, Weapon 3 Ammo)
	// I suggest you use SetPlayerSpawn most of the time instead of 'SetPlayerPos' And 'SetPlayerSkin' because using 'SetPlayerSkin' and 'SpawnPlayer' at the same time will crash the player in random even if the player has 100% orginal GTA.
	SetSpawnInfo(
		playerid, playerid, Skin[Player[playerid][Team]], DMSpawn[DMID][0] + RandomMinMax(-1, 1), DMSpawn[DMID][1] + RandomMinMax(-1, 1), DMSpawn[DMID][2], DMSpawn[DMID][3], DMWeapons[DMID][0], 9999,
		DMWeapons[DMID][1], 9999, DMWeapons[DMID][2], 9999);
	Player[playerid][IgnoreSpawn] = true; //Make sure you ignore OnPlayerSpawn, else you will just spawn in lobby (because u are about to use SpawnPlayer).
	SpawnPlayer(playerid);				  //Spawns players, in this case we have SetSpawnInfo (but still you need to make sure OnPlayerSpawn is ignored);
	SetPlayerInterior(playerid, DMInterior[DMID]);
	SetPlayerTeam(playerid, NO_TEAM);

	// If the second and third weapons are punch or no weapons then it'll show you just one weapon instead of saying (Deagle - Punch - Punch)
	if (DMWeapons[DMID][1] == 0 && DMWeapons[DMID][2] == 0)
		va_SendClientMessageToAll(-1, "%s " COL_PRIM "has entered DM %d {FFFFFF}(%s).", Player[playerid][Name], DMID, ReturnWeaponName(DMWeapons[DMID][0]));
	//If only the third weapons is punch then it'll show two weapons e.g. (Deagle - Shotgun) instead of (Deagle - Shotgun - Punch)
	else if (DMWeapons[DMID][2] == 0)
		va_SendClientMessageToAll(
			-1, "%s " COL_PRIM "has entered DM %d {FFFFFF}(%s - %s).", Player[playerid][Name], DMID, ReturnWeaponName(DMWeapons[DMID][0]),
			ReturnWeaponName(DMWeapons[DMID][1]));
	//If all the weapons are known then it'll show u all three weapons e.g. (Deagle - Shotgun - Sniper)
	else
		va_SendClientMessageToAll(
			-1, "%s " COL_PRIM "has entered DM %d {FFFFFF}(%s - %s - %s).", Player[playerid][Name], DMID, ReturnWeaponName(DMWeapons[DMID][0]),
			ReturnWeaponName(DMWeapons[DMID][1]), ReturnWeaponName(DMWeapons[DMID][2]));

	if (Player[playerid][BeingSpeced])
	{
		foreach (new i : Player)
		{
			if (Player[i][Spectating] && Player[i][IsSpectatingID] == playerid)
			{
				StopSpectate(i);
			}
		}
	}
	return 1;
}
