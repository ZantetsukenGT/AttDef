#if defined _attdef_OnRconLoginAttempt
	#endinput
#endif
#define _attdef_OnRconLoginAttempt

public OnRconLoginAttempt(ip[], password[], success)
{
	new Str[144], iName[MAX_PLAYER_NAME], playerid, IP[16];
	foreach (new i : Player)
	{
		GetPlayerIp(i, IP, sizeof(IP));
		if (!strcmp(IP, ip))
		{
			GetPlayerName(i, iName, sizeof(iName));
			playerid = i;
		}
	}

	if (!success)
	{
		format(Str, sizeof(Str), "{FFFFFF}%s " COL_PRIM "has failed to log into rcon.", iName);
		SendClientMessageToAll(-1, Str);

		Player[playerid][RconTry]++;

		if (Player[playerid][RconTry] >= 2)
		{
			format(Str, sizeof(Str), "{FFFFFF}%s " COL_PRIM "has been kicked for several fail attempts to log into rcon", iName);
			SendClientMessageToAll(-1, Str);
			SetTimerEx("OnPlayerKicked", GetPlayerPing(playerid) + 10, false, "i", playerid);
			return 1;
		}
		else
			SendClientMessage(playerid, -1, "Wrong password one more time will get you kicked.");
	}
	else
	{
		format(Str, sizeof(Str), "UPDATE Players SET Level = %d WHERE Name = '%q' AND Level != %d", Player[playerid][Level], Player[playerid][Name], Player[playerid][Level]);
		db_free_result(db_query(sqliteconnection, Str));
		if (Player[playerid][Level] != 5)
		{
			if (Player[playerid][Level] == 0)
			{
				// Previous level was 0. This means it's a new admin. Guide them.
				SendClientMessage(playerid, -1, COL_PRIM "Looks like you're a new admin. Type {FFFFFF}/acmds " COL_PRIM " to see a list of admin commands!");
			}
			Player[playerid][Level] = 5;
			UpdatePlayerAdminGroup(playerid);
			format(Str, sizeof(Str), "UPDATE Players SET Level = %d WHERE Name = '%q'", Player[playerid][Level], Player[playerid][Name]);
			db_free_result(db_query(sqliteconnection, Str));

			format(Str, sizeof(Str), "{FFFFFF}%s " COL_PRIM "has successfully logged into rcon and got level 5.", iName);
		}
		else
			format(Str, sizeof(Str), "{FFFFFF}%s " COL_PRIM "has successfully logged into rcon.", iName);
		foreach (new j : Player)
		{
			if (Player[j][Level] > 4)
				SendClientMessage(j, -1, Str);
		}
	}
	return 1;
}
