#if defined _attdef_cmd_para
	#endinput
#endif
#define _attdef_cmd_para

YCMD: para(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "get rid of your parachute.");

	RemovePlayerWeapon(playerid, 46);
	return SendClientMessage(playerid, -1, "Parachute removed.");
}
