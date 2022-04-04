#if defined _attdef_cmd_aka
	#endinput
#endif
#define _attdef_cmd_aka

YCMD: aka(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "fetch AKA data of a player.");

	new pID;
	if (sscanf(params, "u", pID))
		return SendUsageMessage(playerid, "/aka [Player ID]");

	return PerformCommandAKA(playerid, pID);
}

PerformCommandAKA(playerid, targetid)
{
	if (!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "That player is not connected.");

	new AKAString[256];
	GetPlayerAKA(targetid, AKAString, sizeof(AKAString));

	new title[39];
	format(title, sizeof(title), COL_PRIM "%s's AKA", Player[targetid][Name]);
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, title, AKAString, "Close", "");
}
