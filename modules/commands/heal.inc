#if defined _attdef_cmd_heal
	#endinput
#endif
#define _attdef_cmd_heal

YCMD: heal(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "restore your health and armour.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't heal while playing.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");

	SetHP(playerid, 100);
	SetAP(playerid, 100);
	return 1;
}
