#if defined _attdef_cmd_get
	#endinput
#endif
#define _attdef_cmd_get

YCMD: get(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You Need To Be An Admin.");
	if (help)
		return SendCommandHelpMessage(playerid, "teleport a player to you.");
	new gid;
	if (sscanf(params, "r", gid))
		return SendUsageMessage(playerid, "/get [Player Name/ID]");

	if (gid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Player isn't connected.");
	if (gid == playerid)
		return SendErrorMessage(playerid, "Can't get yourself.");

	new Float: x,
		Float: y,
		Float: z;
	GetPlayerPos(playerid, x, y, z);

	if (GetPlayerState(gid) == PLAYER_STATE_DRIVER)
	{
		SetVehiclePos(GetPlayerVehicleID(gid), x + 2, y, z);
		LinkVehicleToInterior(GetPlayerVehicleID(gid), GetPlayerInterior(playerid));
		SetVehicleVirtualWorld(GetPlayerVehicleID(gid), GetPlayerVirtualWorld(playerid));
	}
	else
		SetPlayerPos(gid, x + 1, y, z);

	SetPlayerInterior(gid, GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(gid, GetPlayerVirtualWorld(playerid));

	LogAdminCommand("get", playerid, gid);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has teleported {FFFFFF}%s " COL_PRIM "to himself.", Player[playerid][Name], Player[gid][Name]);
}
