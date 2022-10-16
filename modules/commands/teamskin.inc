#if defined _attdef_cmd_teamskin
	#endinput
#endif
#define _attdef_cmd_teamskin

YCMD: teamskin(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "change the skin of a team.");
	if (ChangingSkinOfTeam[playerid] != -1)
		return SendErrorMessage(playerid, "You're already changing team skins.");
	/*if (isnull(params))
		return SendUsageMessage(playerid, "/teamskin [Team ID: 0 Attacker | 1 Defender | 2 Referee] [optional: skin id]");*/
	new teamid, skin[8];
	if (sscanf(params, "iS( )[8]", teamid, skin))
		return SendUsageMessage(playerid, "/teamskin [Team ID: 0 Attacker | 1 Defender | 2 Referee] [optional: skin id]");
	if (teamid < 0 || teamid > 2)
		return SendErrorMessage(playerid, "Invalid team ID.");

	ChangingSkinOfTeam[playerid] = teamid + 1;
	if (isnull(skin))
	{
		switch (ChangingSkinOfTeam[playerid])
		{
			case ATTACKER: ShowModelSelectionMenu(playerid, teamskinlist, "Select Attacker Team Skin", 0xFA1E1EBB, 0xFFA8A899, 0xFCCACAAA);
			case DEFENDER: ShowModelSelectionMenu(playerid, teamskinlist, "Select Defender Team Skin", 0x323FF0BB, 0x9097F599, 0xDCDEF7AA);
			case REFEREE: ShowModelSelectionMenu(playerid, teamskinlist, "Select Referee Team Skin", 0xDCF72ABB, 0xEAF79299, 0xEBF2BBAA);
			default: ShowModelSelectionMenu(playerid, teamskinlist, "Select Team Skin");
		}
		LogAdminCommand("teamskin", playerid, INVALID_PLAYER_ID);
		return 1;
	}
	
	new skinid = strval(skin);
	if (!IsValidSkin(skinid))
		return SendErrorMessage(playerid, "Invalid skin id");

	new iString[128];
	switch (ChangingSkinOfTeam[playerid])
	{
		case ATTACKER:
		{
			Skin[ATTACKER] = skinid;

			format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Attacker Skin'", Skin[ATTACKER]);
			db_free_result(db_query(sqliteconnection, iString));
		}
		case DEFENDER:
		{
			Skin[DEFENDER] = skinid;

			format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Defender Skin'", Skin[DEFENDER]);
			db_free_result(db_query(sqliteconnection, iString));
		}
		case REFEREE:
		{
			Skin[REFEREE] = skinid;

			format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Referee Skin'", Skin[REFEREE]);
			db_free_result(db_query(sqliteconnection, iString));
		}
	}

	foreach (new i : Player)
	{
		if (Player[i][Team] == ChangingSkinOfTeam[playerid])
			SetPlayerSkin(i, skinid);
	}

	LogAdminCommand("teamskin", playerid, INVALID_PLAYER_ID);

	format(
		iString, sizeof(iString), "%s " COL_PRIM "has changed {FFFFFF}%s " COL_PRIM "skin to: {FFFFFF}%d", Player[playerid][Name], TeamName[ChangingSkinOfTeam[playerid]],
		skinid);
	ChangingSkinOfTeam[playerid] = -1;
	return SendClientMessageToAll(-1, iString);
}
