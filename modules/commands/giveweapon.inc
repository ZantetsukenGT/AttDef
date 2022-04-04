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
	new pID, Weapon[50], Ammo;

	if (sscanf(params, "is[50]d", pID, Weapon, Ammo))
		return SendUsageMessage(playerid, "/giveweapon [Player ID] [Weapon Name] [Ammo]");

	if (Ammo < 0 || Ammo > 9999)
		return SendErrorMessage(playerid, "Invalid Ammo.");

	new WeaponID = GetWeaponID(Weapon);
	if (WeaponID < 1 || WeaponID > 46 || WeaponID == 19 || WeaponID == 20 || WeaponID == 21 || WeaponID == 22)
		return SendErrorMessage(playerid, "Invalid Weapon Name.");
	if (WeaponID == 44 || WeaponID == 45)
		return SendErrorMessage(playerid, "We don't do this shit around here.");

	GivePlayerWeapon(pID, WeaponID, Ammo);

	LogAdminCommand("giveweapon", playerid, pID);

	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has given {FFFFFF}%s " COL_PRIM "a {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name],
		Player[pID][Name], WeaponNames[WeaponID]));
}
