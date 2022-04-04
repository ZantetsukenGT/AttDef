#if defined _attdef_cmd_dm
	#endinput
#endif
#define _attdef_cmd_dm

YCMD: dm(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "teleport you to a deathmatch arena.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/dm [DM ID]");
	if (!IsNumeric(params))
		return SendErrorMessage(playerid, "DM id can only be numeric.");
	if (Player[playerid][Playing])
		return 1;

	new DMID = strval(params);

	// Here I also added '=' after '>' so that if the DMID was Bigger than or Equal to MAX_DMS then you get that error message.
	// Without this '=' (equal sign) if you type /dm 15 it will say the command is unkown which is a script error.
	if (DMID >= MAX_DMS)
		return SendErrorMessage(playerid, "Invalid DM id."); // If you don't use this line and later on you use 'crashdetect' plugin for ur gamemode, it will give you an error.
	if (!DMExist[DMID])
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
	SetPlayerTeam(playerid, playerid);

	new iString[140];

	// If the second and third weapons are punch or no weapons then it'll show you just one weapon instead of saying (Deagle - Punch - Punch)
	if (DMWeapons[DMID][1] == 0 && DMWeapons[DMID][2] == 0)
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has entered DM %d {FFFFFF}(%s).", Player[playerid][Name], DMID, WeaponNames[DMWeapons[DMID][0]]);
	//If only the third weapons is punch then it'll show two weapons e.g. (Deagle - Shotgun) instead of (Deagle - Shotgun - Punch)
	else if (DMWeapons[DMID][2] == 0)
		format(
			iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has entered DM %d {FFFFFF}(%s - %s).", Player[playerid][Name], DMID, WeaponNames[DMWeapons[DMID][0]],
			WeaponNames[DMWeapons[DMID][1]]);
	//If all the weapons are known then it'll show u all three weapons e.g. (Deagle - Shotgun - Sniper)
	else
		format(
			iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has entered DM %d {FFFFFF}(%s - %s - %s).", Player[playerid][Name], DMID, WeaponNames[DMWeapons[DMID][0]],
			WeaponNames[DMWeapons[DMID][1]], WeaponNames[DMWeapons[DMID][2]]);

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
	return SendClientMessageToAll(-1, iString); // Send the formatted message to everyone.
}
