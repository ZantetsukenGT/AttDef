#if defined _attdef_cmd_back
	#endinput
#endif
#define _attdef_cmd_back

YCMD: back(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "get you out of AFK mode.");
	if (!Player[playerid][IsAFK])
		return SendErrorMessage(playerid, "You are not AFK?");

	Player[playerid][Team] = REFEREE;
	TogglePlayerControllable(playerid, 1);
	Player[playerid][IsAFK] = false;
	SetHP(playerid, 100);

	new iString[128];
	format(iString, sizeof(iString), "%s " COL_PRIM "is back from {FFFFFF}AFK mode" COL_PRIM ".", Player[playerid][Name]);
	SendClientMessageToAll(-1, iString);
	format(
		iString, sizeof(iString), "%s%s\n%s%s\n%sReferee\n%s%s Sub\n%s%s Sub", TextColor[ATTACKER], TeamName[ATTACKER], TextColor[DEFENDER], TeamName[DEFENDER], TextColor[REFEREE],
		TextColor[ATTACKER_SUB], TeamName[ATTACKER], TextColor[DEFENDER_SUB], TeamName[DEFENDER]);
	return ShowPlayerDialog(playerid, DIALOG_SWITCH_TEAM, DIALOG_STYLE_LIST, "{FFFFFF}Team Selection", iString, "Select", "");
}
