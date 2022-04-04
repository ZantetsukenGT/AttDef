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

	new invitedid, Weapon1[23], Weapon2[23], duelarena[8], sizeStr[8];
	if (sscanf(params, "is[23]s[23]S( )[8]S( )[8]", invitedid, Weapon1, Weapon2, duelarena, sizeStr))
	{
		SendUsageMessage(playerid, "/duel [Player ID] [Weapon 1] [Weapon 2] [Optional: default/custom] [Optional: area size]");
		return SendClientMessage(playerid, -1, "" COL_PRIM "Note: {FFFFFF}[custom] to play in your current place and [default] for default duel arena");
	}
	if (!IsPlayerConnected(invitedid))
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
	if (WeaponID1 < 1 || WeaponID1 > 46 || WeaponID1 == 19 || WeaponID1 == 20 || WeaponID1 == 21)
		return SendErrorMessage(playerid, "Invalid Weapon Name.");
	if (WeaponID1 == 40 || WeaponID1 == 43 || WeaponID1 == 44 || WeaponID1 == 45)
		return SendErrorMessage(playerid, "That weapon is not allowed in duels.");

	new WeaponID2 = GetWeaponID(Weapon2);
	if (WeaponID2 < 1 || WeaponID2 > 46 || WeaponID2 == 19 || WeaponID2 == 20 || WeaponID2 == 21)
		return SendErrorMessage(playerid, "Invalid Weapon Name.");
	if (WeaponID2 == 40 || WeaponID2 == 43 || WeaponID2 == 44 || WeaponID2 == 45)
		return SendErrorMessage(playerid, "That weapon is not allowed in duels.");

	new duelarenaid;
	switch (YHash(duelarena, false))
	{
		case _I<default>: duelarenaid = DEFAULT_DUEL_ARENA_ID;
		case _I<custom>: duelarenaid = 1 + DEFAULT_DUEL_ARENA_ID;
		default: duelarenaid = DEFAULT_DUEL_ARENA_ID;
	}

	new size = 90;
	if (!isnull(sizeStr))
	{
		size = strval(sizeStr);
		if (size < 50)
			size = 50;
	}
	return ProcessDuelRequest(playerid, invitedid, WeaponID1, WeaponID2, duelarenaid, size);
}
