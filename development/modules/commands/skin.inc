#if defined _attdef_cmd_skin
	#endinput
#endif
#define _attdef_cmd_skin

YCMD: skin(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "view a catalog of different skins.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command while playing.");
	if (Player[playerid][Spectating])
		return 1;

	return ShowModelSelectionMenu(playerid, playerskinlist, "Select a skin", 0x000000BB, 0x44444499, 0x99999999);
}
