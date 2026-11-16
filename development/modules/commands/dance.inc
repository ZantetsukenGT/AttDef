#if defined _attdef_cmd_dance
	#endinput
#endif
#define _attdef_cmd_dance

YCMD: dance(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "shake your fucking ass.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this command while in round.");
	new dID = strval(params);
	if (sscanf(params, "i", dID) || dID < 1 || dID > 4)
		return SendUsageMessage(playerid, "/dance [1-4]");

	switch (dID)
	{
		case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
		case 2: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
		case 3: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
		case 4: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
	}
	return 1;
}
