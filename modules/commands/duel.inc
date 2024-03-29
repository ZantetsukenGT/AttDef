#if defined _attdef_cmd_duel
	#endinput
#endif
#define _attdef_cmd_duel

YCMD: duel(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "send a duel request to a specific player.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "You are already dueling someone.");

	new invitedid, Weapon1[23], Weapon2[23], duelarena[8], size;
	if (sscanf(params, "rs[*]s[*]S( )[8]I(90)", invitedid, sizeof(Weapon1), Weapon1, sizeof(Weapon2), Weapon2, duelarena, size))
	{
		SendUsageMessage(playerid, "/duel [Player Name/ID] [Weapon 1] [Weapon 2] [Optional: default/custom] [Optional: area size]");
		return SendClientMessage(playerid, -1, "" COL_PRIM "Note: {FFFFFF}[custom] to play in your current place and [default] for default duel arena");
	}
	if (invitedid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (Player[invitedid][Playing])
		return SendErrorMessage(playerid, "That player is in a round.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "You can't duel while being in a round.");
	if (Player[invitedid][InDuel])
		return SendErrorMessage(playerid, "That player is already dueling someone.");
	if (Player[invitedid][challengerid] == playerid)
		return SendErrorMessage(playerid, "You have already invited that player for duel. Let him accept or deny your previous invite."); //duelspamfix
	if (invitedid == playerid)
		return SendErrorMessage(playerid, "Can't duel with yourself.");

	new WeaponID1 = GetWeaponID(Weapon1);
	if (!IsValidWeapon(WeaponID1))
		return SendErrorMessage(playerid, "Invalid Weapon Name.");

	new WeaponID2 = GetWeaponID(Weapon2);
	if (!IsValidWeapon(WeaponID2))
		return SendErrorMessage(playerid, "That weapon is not allowed in duels.");

	new duelarenaid;
	switch (YHash(duelarena, false))
	{
		case _I<custom>: duelarenaid = 1 + DEFAULT_DUEL_ARENA_ID;
		default: duelarenaid = DEFAULT_DUEL_ARENA_ID;
	}
	size = max(size, 50);
	return ProcessDuelRequest(playerid, invitedid, WeaponID1, WeaponID2, duelarenaid, size);
}
