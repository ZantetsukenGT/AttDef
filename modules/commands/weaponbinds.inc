#if defined _attdef_cmd_weaponbinds
	#endinput
#endif
#define _attdef_cmd_weaponbinds

YCMD: weaponbinds(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "code your weapon bind keys");
	return ShowPlayerWeaponBindDialog(playerid);
}
