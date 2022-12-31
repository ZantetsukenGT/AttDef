#if defined _attdef_cmd_ban
	#endinput
#endif
#define _attdef_cmd_ban

YCMD: ban(playerid, params[], help)
{
	//if(Player[playerid][Level] < 3 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "ban a specific player from the server.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Can't ban now. Please wait.");

	new pID, Reason[128];
	if (sscanf(params, "rS( )[128]", pID, Reason))
		return SendUsageMessage(playerid, "/ban [Player Name/ID] [Reason]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (Player[pID][Level] >= Player[playerid][Level])
		return SendErrorMessage(playerid, "Cannot ban someone of the same or higher admin level as you.");

	if (isnull(Reason))
		va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has banned {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name], Player[pID][Name]);
	else
		va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has banned {FFFFFF}%s" COL_PRIM ". | Reason: {FFFFFF}%s", Player[playerid][Name], Player[pID][Name], Reason);

	SetTimerEx("BanExDelayed", GetPlayerPing(playerid) + 10, false, "ds", pID, va_return("%s - %s", Player[playerid][Name], Reason));
	return LogAdminCommand("ban", playerid, pID);
}

forward BanExDelayed(playerid, const reason[]);
public BanExDelayed(playerid, const reason[]) { BanEx(playerid, reason); }

forward _BanPlayerDelayed(playerid);
public _BanPlayerDelayed(playerid)
{
	Ban(playerid);
	return 1;
}
