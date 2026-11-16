#if defined _attdef_cmd_reset
	#endinput
#endif
#define _attdef_cmd_reset

YCMD: reset(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "reset gunmenu selections.");
	if (!Player[playerid][OnGunmenu])
		return SendErrorMessage(playerid, "You're not selecting weapons from gunmenu");
	if (Player[playerid][GunmenuStyle] != GUNMENU_STYLE_OBJECT)
		return SendErrorMessage(playerid, "This command is available only in gunmenu objects style.");

	ResetPlayerGunmenu(playerid, true);
	return 1;
}
