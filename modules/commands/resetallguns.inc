#if defined _attdef_cmd_resetallguns
	#endinput
#endif
#define _attdef_cmd_resetallguns

YCMD: resetallguns(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "reset guns of all players.");
	foreach (new i : Player)
	{
		if (!Player[i][InDM] && !Player[i][InDuel] && !Player[i][Spectating])
			ResetPlayerWeapons(i);
	}

	LogAdminCommand("resetallguns", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has reset everyone's weapons.", Player[playerid][Name]);
}
