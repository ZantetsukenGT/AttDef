#if defined _attdef_cmd_remgun
	#endinput
#endif
#define _attdef_cmd_remgun

YCMD: remgun(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "remove the gun you currently holding from your inventory");
	new weaponID = GetPlayerWeapon(playerid);
	if (weaponID == 0)
		return SendErrorMessage(playerid, "You wanna remove your hand? Visit a doctor, we don't do surgery here!");

	RemovePlayerWeapon(playerid, weaponID);
	return va_SendClientMessage(playerid, -1, "Removed %s from your gun inventory!", ReturnWeaponName(weaponID));
}
