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
	if (sscanf(params, "s[50]d", Weapon, Ammo))
		return SendUsageMessage(playerid, "/giveallgun [Weapon Name] [Ammo]");

	if (Ammo < 0 || Ammo > 9999)
		return SendErrorMessage(playerid, "Invalid Ammo.");

	new weapon = GetWeaponID(Weapon);
	if (weapon < 1 || weapon > 46 || weapon == 19 || weapon == 20 || weapon == 21 || weapon == 22)
		return SendErrorMessage(playerid, "Invalid weapon name.");
	if (weapon == 44 || weapon == 45)
		return SendErrorMessage(playerid, "We don't do this shit around here.");

	foreach (new i : Player)
	{
		if (!Player[i][InDM] && !Player[i][InDuel] && !Player[i][Spectating])
		{
			GivePlayerWeapon(i, weapon, Ammo);
		}
	}

	LogAdminCommand("giveallgun", playerid, INVALID_PLAYER_ID);

	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has given everyone | Weapon: {FFFFFF}%s " COL_PRIM "- Ammo: {FFFFFF}%d", Player[playerid][Name], WeaponNames[weapon],
		Ammo));
}
