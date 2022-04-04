#if defined _attdef_OnPModelSelection
	#endinput
#endif
#define _attdef_OnPModelSelection

public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if (listid == teamskinlist)
	{
		if (response && ChangingSkinOfTeam[playerid] != -1)
		{
			new iString[128];
			switch (ChangingSkinOfTeam[playerid])
			{
				case ATTACKER:
				{
					Skin[ATTACKER] = modelid;

					format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Attacker Skin'", Skin[ATTACKER]);
					db_free_result(db_query(sqliteconnection, iString));
				}
				case DEFENDER:
				{
					Skin[DEFENDER] = modelid;

					format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Defender Skin'", Skin[DEFENDER]);
					db_free_result(db_query(sqliteconnection, iString));
				}
				case REFEREE:
				{
					Skin[REFEREE] = modelid;

					format(iString, sizeof(iString), "UPDATE Configs SET Value = %d WHERE Option = 'Referee Skin'", Skin[REFEREE]);
					db_free_result(db_query(sqliteconnection, iString));
				}
			}

			foreach (new i : Player)
			{
				if (Player[i][Team] == ChangingSkinOfTeam[playerid])
				{
					SetPlayerSkin(i, modelid);
				}
			}

			format(
				iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed {FFFFFF}%s " COL_PRIM "skin to: {FFFFFF}%d", Player[playerid][Name],
				TeamName[ChangingSkinOfTeam[playerid]], modelid);
			SendClientMessageToAll(-1, iString);
			ChangingSkinOfTeam[playerid] = -1;
		}
		else
		{
			ChangingSkinOfTeam[playerid] = -1;
			SendClientMessage(playerid, -1, "Canceled team skin selection");
		}
	}
	else if (listid == playerskinlist)
	{
		if (response && !Player[playerid][Playing] && !Player[playerid][Spectating])
		{
			SetPlayerSkin(playerid, modelid);
		}
	}
	return 1;
}
