#if defined _attdef_cmd_giveweapon
	#endinput
#endif
#define _attdef_cmd_giveweapon

YCMD: giveweapon(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "give a weapon to a specific player.");

	new pID, Weapon[WC_MAX_WEAPON_NAME], Ammo;
	if (sscanf(params, "is[*]I(250)", pID, WC_MAX_WEAPON_NAME, Weapon, Ammo))
		return SendUsageMessage(playerid, "/giveweapon [Player ID] [Weapon Name] [Optional: Ammo]");

	new WeaponID = GetWeaponID(Weapon);
	if (!IsValidWeapon(WeaponID))
		return SendErrorMessage(playerid, "Invalid Weapon.");

	Ammo = clamp(Ammo, 10, 9999);

	GivePlayerWeapon(pID, WeaponID, Ammo);

	LogAdminCommand("giveweapon", playerid, pID);

	return va_SendClientMessageToAll(
		-1, "{FFFFFF}%s " COL_PRIM "has given {FFFFFF}%s " COL_PRIM "a {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name], Player[pID][Name], ReturnWeaponName(WeaponID));
}
