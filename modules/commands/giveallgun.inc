#if defined _attdef_cmd_giveallgun
	#endinput
#endif
#define _attdef_cmd_giveallgun

YCMD: giveallgun(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "give everyone a specific weapon.");
	new Weapon[50], Ammo;
	if (sscanf(params, "s[*]I(250)", sizeof(Weapon), Weapon, Ammo))
		return SendUsageMessage(playerid, "/giveallgun [Weapon Name] [Optional: Ammo]");

	new WeaponID = GetWeaponID(Weapon);
	if (!IsValidWeapon(WeaponID))
		return SendErrorMessage(playerid, "Invalid Weapon Name.");

	Ammo = clamp(Ammo, 10, 9999);

	foreach (new i : Player)
	{
		if (!Player[i][InDM] && !Player[i][InDuel] && !Player[i][Spectating])
		{
			GivePlayerWeapon(i, WeaponID, Ammo);
		}
	}

	LogAdminCommand("giveallgun", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has given everyone {FFFFFF}%s " COL_PRIM "with {FFFFFF}%d " COL_PRIM "ammo.", Player[playerid][Name], ReturnWeaponName(WeaponID),
		Ammo);
}
