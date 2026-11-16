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
	if (sscanf(params, "rs[*]I(250)", pID, sizeof(Weapon), Weapon, Ammo))
		return SendUsageMessage(playerid, "/giveweapon [Player Name/ID] [Weapon Name] [Optional: Ammo]");
	if (pID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");

	Ammo = clamp(Ammo, 10, 9999);

	new WeaponID = GetWeaponID(Weapon);
	if (!IsValidWeapon(WeaponID))
		return SendErrorMessage(playerid, "Invalid Weapon Name.");

	GivePlayerWeapon(pID, WeaponID, Ammo);

	LogAdminCommand("giveweapon", playerid, pID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has given {FFFFFF}%s " COL_PRIM "a {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name],
		Player[pID][Name], ReturnWeaponName(WeaponID));
}
