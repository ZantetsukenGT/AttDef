#if defined _attdef_cmd_kick
	#endinput
#endif
#define _attdef_cmd_kick

YCMD: kick(playerid, params[], help)
{
	//if(Player[playerid][Level] < 3 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "kick a specific player from the server.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Can't kick now. Please wait.");

	new pID, reason[128];
	if (sscanf(params, "dS( )[128]", pID, reason))
		return SendUsageMessage(playerid, "/kick [Player ID] [Reason]");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (Player[pID][Level] >= Player[playerid][Level])
		return SendErrorMessage(playerid, "Cannot kick someone of the same admin level as you or higher.");

	new iString[180];
	if (isnull(reason))
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has kicked {FFFFFF}%s " COL_PRIM "| Reason: {FFFFFF}No Reason Given", Player[playerid][Name], Player[pID][Name]);
	else
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has kicked {FFFFFF}%s " COL_PRIM "| Reason: {FFFFFF}%s", Player[playerid][Name], Player[pID][Name], reason);

	SetTimerEx("OnPlayerKicked", 350, false, "i", pID);
	LogAdminCommand("kick", playerid, pID);
	return SendClientMessageToAll(-1, iString);
}
