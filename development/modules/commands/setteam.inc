#if defined _attdef_cmd_setteam
	#endinput
#endif
#define _attdef_cmd_setteam

YCMD: setteam(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set the team of a player.");

	new pID, teamID;
	if (sscanf(params, "rd", pID, teamID))
		return SendUsageMessage(playerid, "/setteam [Player Name/ID] [Team ID | 0 Att | 1 Def | 2 Ref | 3 Att_Sub | 4 Def_Sub]");

	if (teamID < 0 || teamID > 4)
		return SendErrorMessage(playerid, "Invalid team ID.");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (Player[pID][Playing])
		return SendErrorMessage(playerid, "That player is playing.");
	if (Player[pID][Spectating])
		StopSpectate(pID);

	new MyVehicle = -1;
	new Seat;

	if (IsPlayerInAnyVehicle(pID))
	{
		MyVehicle = GetPlayerVehicleID(pID);
		Seat	  = GetPlayerVehicleSeat(pID);
	}

	Player[pID][Team] = teamID + 1;
	SetPlayerSkin(pID, Skin[teamID + 1]);
	ColorFix(pID);

	if (Current != -1)
	{
		ShowTeamBarsForPlayer(pID);
		ShowTeamCornerInfo(pID);
	}

	if (MyVehicle != -1)
		PutPlayerInVehicle(pID, MyVehicle, Seat);

	SwitchTeamFix(pID, false, true);

	UpdateRoundKillDmgTDmg(pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has switched {FFFFFF}%s " COL_PRIM "to: {FFFFFF}%s", Player[playerid][Name], Player[pID][Name], TeamName[teamID + 1]);
}
