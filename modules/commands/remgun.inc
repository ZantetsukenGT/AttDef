#if defined _attdef_cmd_remgun
	#endinput
#endif
#define _attdef_cmd_remgun

YCMD: remgun(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "remove the gun you currently holding from your inventory");
	if (GetPlayerWeapon(playerid) == 0)
		return SendErrorMessage(playerid, "You wanna remove your hand? Visit a doctor, we don't do surgery here!");

	RemovePlayerWeapon(playerid, GetPlayerWeapon(playerid));
	return SendClientMessage(playerid, -1, va_return("Removed %s from your gun inventory!", WeaponNames[GetPlayerWeapon(playerid)]));
}
