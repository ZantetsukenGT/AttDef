#if defined _attdef_cmd_ann
	#endinput
#endif
#define _attdef_cmd_ann

YCMD: ann(playerid, params[], help)
{
	//if(Player[playerid][Level] < 2) return SendErrorMessage(playerid,"You must be a higher level admin to use this command.");
	if (help)
		return SendCommandHelpMessage(playerid, "display a specific announcement to all players");
	new str[128];
	if (sscanf(params, "s[128]", str))
		return SendUsageMessage(playerid, "/ann [Text]");
	if (strfind(str, "`") != -1)
		return SendErrorMessage(playerid, "` is not allowed.");
	if (!IsSafeGametext(str))
	{
		SendErrorMessage(playerid, "You're probably missing a '~' which can crash you and/or other clients!");
		return SendClientMessage(playerid, -1, "{FFFFFF}Note: " COL_PRIM "Always leave a space between a '~' and the character 'K'");
	}

	if (AnnTimer)
		KillTimer(AnnTimer);
	AnnTimer = SetTimer("HideAnnForAll", 5000, false);

	TextDrawSetString(AnnTD, str);
	TextDrawShowForAll(AnnTD);

	LogAdminCommand("ann", playerid, INVALID_PLAYER_ID);

	format(str, sizeof(str), "%s " COL_PRIM "showed an announcement.", Player[playerid][Name]);
	return SendClientMessageToAll(-1, str);
}
