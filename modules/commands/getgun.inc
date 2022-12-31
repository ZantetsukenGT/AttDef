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
	if (sscanf(params, "s[*]I(250)", sizeof(Weapon), Weapon, Ammo))
		return SendUsageMessage(playerid, "/getgun [Weapon Name] [Optional: Ammo]");

	new WeaponID = GetWeaponID(Weapon);
	if (!IsValidWeapon(WeaponID))
		return SendErrorMessage(playerid, "Invalid Weapon Name.");

	Ammo = clamp(Ammo, 10, 9999);

	GivePlayerWeapon(playerid, WeaponID, Ammo);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has given himself {FFFFFF}%s " COL_PRIM "with {FFFFFF}%d " COL_PRIM "ammo.", Player[playerid][Name],
		ReturnWeaponName(WeaponID), Ammo);
}
