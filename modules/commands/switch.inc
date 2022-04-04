#if defined _attdef_cmd_switch
	#endinput
#endif
#define _attdef_cmd_switch

YCMD: switch (playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your team.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't switch while playing.");
	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	new iString[256];
	format(
		iString, sizeof(iString), "%s%s\n%s%s\n%sReferee\n%s%s Sub\n%s%s Sub", TextColor[ATTACKER], TeamName[ATTACKER], TextColor[DEFENDER], TeamName[DEFENDER], TextColor[REFEREE],
		TextColor[ATTACKER_SUB], TeamName[ATTACKER], TextColor[DEFENDER_SUB], TeamName[DEFENDER]);
	return ShowPlayerDialog(playerid, DIALOG_SWITCH_TEAM, DIALOG_STYLE_LIST, "{FFFFFF}Team Selection", iString, "Select", "Exit");
}
