#if defined _attdef_cmd_move
	#endinput
#endif
#define _attdef_cmd_move

YCMD: move(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "teleport a player to another player.");
	new pID[2];
	if (sscanf(params, "rr", pID[0], pID[1]))
		return SendUsageMessage(playerid, "/move [PlayerToMove Name/ID] [PlayerToMoveTo Name/ID]");
	if (pID[0] == INVALID_PLAYER_ID || pID[1] == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "One of the players you specified is not connected.");

	new Float: Pos[3];
	GetPlayerPos(pID[1], Pos[0], Pos[1], Pos[2]);

	SetPlayerInterior(pID[0], GetPlayerInterior(pID[1]));
	SetPlayerVirtualWorld(pID[0], GetPlayerVirtualWorld(pID[1]));

	if (GetPlayerState(pID[0]) == 2)
	{
		SetVehiclePos(GetPlayerVehicleID(pID[0]), Pos[0] + 3, Pos[1], Pos[2]);
		LinkVehicleToInterior(GetPlayerVehicleID(pID[0]), GetPlayerInterior(pID[1]));
		SetVehicleVirtualWorld(GetPlayerVehicleID(pID[0]), GetPlayerVirtualWorld(pID[1]));
	}
	else
		SetPlayerPos(pID[0], Pos[0] + 2, Pos[1], Pos[2]);

	LogAdminCommand("move", playerid, pID[0]);

	new iString[144];
	format(iString, sizeof(iString), "%s " COL_PRIM "has moved {FFFFFF}%s " COL_PRIM "to {FFFFFF}%s", Player[playerid][Name], Player[pID[0]][Name], Player[pID[1]][Name]);
	return SendClientMessageToAll(-1, iString);
}
