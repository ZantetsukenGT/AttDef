#if defined _attdef_cmd_armourall
	#endinput
#endif
#define _attdef_cmd_armourall

YCMD: armourall(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "restore everyone's armour.");
	if (Current == -1)
		return SendErrorMessage(playerid, "There is no active round.");

	foreach (new i : Player)
	{
		if (Player[i][Playing])
			SetAP(i, 100);
	}
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has {FFFFFF}armoured " COL_PRIM "everyone.", Player[playerid][Name]);
}
