#if defined _attdef_cmd_getgun
	#endinput
#endif
#define _attdef_cmd_getgun

YCMD: getgun(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "give you a specific weapon");
	if (!LobbyGuns)
		return SendErrorMessage(playerid, "Guns in lobby are disabled.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command while playing.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel. Use /rq instead.");
	if (Player[playerid][InDM])
		return SendErrorMessage(playerid, "Can't use this command during DM.");

	new Weapon[50], Ammo;

	if (sscanf(params, "s[50]d", Weapon, Ammo))
		return SendUsageMessage(playerid, "/getgun [Weapon Name] [Ammo]");

	if (Ammo < 0 || Ammo > 9999)
		return SendErrorMessage(playerid, "Invalid Ammo.");

	new WeaponID = GetWeaponID(Weapon);
	if (WeaponID < 1 || WeaponID > 46 || WeaponID == 19 || WeaponID == 20 || WeaponID == 21 || WeaponID == 22)
		return SendErrorMessage(playerid, "Invalid Weapon Name.");
	if (WeaponID == 44 || WeaponID == 45)
		return SendErrorMessage(playerid, "We don't do this shit around here.");

	GivePlayerWeapon(playerid, WeaponID, Ammo);

	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has given himself {FFFFFF}%s " COL_PRIM "with {FFFFFF}%d " COL_PRIM "ammo.", Player[playerid][Name],
		WeaponNames[WeaponID], Ammo));
}
