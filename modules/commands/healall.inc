#if defined _attdef_cmd_healall
	#endinput
#endif
#define _attdef_cmd_healall

YCMD: healall(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "restore everyone's health.");
	if (Current == -1)
		return SendErrorMessage(playerid, "There is no active round.");

	foreach (new i : Player)
	{
		if (Player[i][Playing])
			SetHP(i, RoundHP);
	}

	return va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has healed everyone.", Player[playerid][Name]);
}
