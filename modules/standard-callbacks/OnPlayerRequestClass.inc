#if defined _attdef_OnPRequestClass
	#endinput
#endif
#define _attdef_OnPRequestClass

forward InlineLogin(playerid, dialogid, response, listitem, string: inputtext[]);
public InlineLogin(playerid, dialogid, response, listitem, string: inputtext[])
{
#pragma unused dialogid, listitem
	if (response)
	{
		if (isnull(inputtext))
		{
			Dialog_ShowCallback(
				playerid, using public InlineLogin<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Login Dialog", "{FFFFFF}Type your password below to log in:", "Login", "Leave");
			return 1;
		}

		if (strfind(inputtext, "%", true) != -1)
		{
			Dialog_ShowCallback(
				playerid, using public InlineLogin<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Login Dialog", "{FFFFFF}Type your password below to log in:", "Login", "Leave");
			return SendErrorMessage(playerid, va_return("This character '%s' is disallowed in user passwords.", "%%"));
		}
		new iString[BCRYPT_HASH_LENGTH];
		new DBResult: res = db_query(sqliteconnection, va_return("SELECT `Password` FROM `Players` WHERE `Name` = '%q'", Player[playerid][Name]));
		db_get_field_assoc(res, "Password", iString);
		db_free_result(res);
		bcrypt_verify(playerid, "OnLoginPassHash", inputtext, iString);
	}
	else
	{
		new iString[128];
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has been kicked from the server for not logging in.", Player[playerid][Name]);
		SendClientMessageToAll(-1, iString);

		SetTimerEx("OnPlayerKicked", GetPlayerPing(playerid) + 10, false, "i", playerid);
	}
	return 1;
}

forward InlineRegister(playerid, dialogid, response, listitem, string: inputtext[]);
public InlineRegister(playerid, dialogid, response, listitem, string: inputtext[])
{
#pragma unused dialogid, listitem
	if (response)
	{
		if (isnull(inputtext))
		{
			Dialog_ShowCallback(
				playerid, using public InlineRegister<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Registration Dialog", "{FFFFFF}Type your password below to register:",
				"Register", "Leave");
			return 1;
		}

		if (strfind(inputtext, "%", true) != -1)
		{
			Dialog_ShowCallback(
				playerid, using public InlineRegister<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Registration Dialog", "{FFFFFF}Type your password below to register:",
				"Register", "Leave");
			return SendErrorMessage(playerid, va_return("This character '%s' is disallowed in user passwords.", "%%"));
		}
		bcrypt_hash(playerid, "OnRegisterPassHash", inputtext, BCRYPT_COST);
	}
	else
	{
		new iString[128];
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has been kicked from the server for not registering.", Player[playerid][Name]);
		SendClientMessageToAll(-1, iString);

		SetTimerEx("OnPlayerKicked", GetPlayerPing(playerid) + 10, false, "i", playerid);
	}
	return 1;
}

forward OnLoginPassHash(playerid, bool: success);
public OnLoginPassHash(playerid, bool: success)
{
	if (!success)
	{
		SendErrorMessage(playerid, "Wrong Password. Please try again.");
		Dialog_ShowCallback(
			playerid, using public InlineLogin<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Login Dialog", "{FFFFFF}Type your password below to log in:", "Login", "Leave");
		return 1;
	}
	new DBResult: res = db_query(sqliteconnection, va_return("SELECT * FROM `Players` WHERE `Name` = '%q'", Player[playerid][Name]));
	LoginPlayer(playerid, res);
	db_free_result(res);
	new teamid = ShouldPlayerBeReadded(playerid);
	if (teamid != -1)
	{
		SetTimerEx("SpawnConnectedPlayer", 250, false, "ii", playerid, teamid);
	}
	else
	{
		ShowPlayerClassSelection(playerid);
	}
	return 1;
}
forward OnRegisterPassHash(playerid);
public OnRegisterPassHash(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);

	new IP[16];
	GetPlayerIp(playerid, IP, sizeof(IP));
	new day, month, year;
	getdate(year, month, day);
	new query[240];
	format(
		query, sizeof(query), "INSERT INTO Players (Name, Password, IP, LastSeen_Day, LastSeen_Month, LastSeen_Year) VALUES('%q', '%q', '%s', %d, %d, %d)",
		Player[playerid][Name], dest, IP, day, month, year);
	db_free_result(db_query(sqliteconnection, query));

	SendClientMessage(playerid, -1, "{009933}Server account: {FFFFFF}successfully registered your account:");

	new teamid = ShouldPlayerBeReadded(playerid);
	if (teamid != -1)
	{
		SetTimerEx("SpawnConnectedPlayer", 250, false, "ii", playerid, teamid);
	}
	else
	{
		ShowPlayerClassSelection(playerid);
	}

	Player[playerid][Level]		  = 0;
	Player[playerid][Weather]	  = MainWeather;
	Player[playerid][Time]		  = MainTime;
	Player[playerid][Logged]	  = true;
	Player[playerid][ChatChannel] = -1;
	Player[playerid][NetCheck]	  = true;
	Player[playerid][DuelsWon]	  = 0;
	Player[playerid][DuelsLost]	  = 0;
}

public OnPlayerRequestClass(playerid, classid)
{
	// Initialize class selection mode
	Player[playerid][Team] = NON;
	SetPlayerColor(playerid, 0xAAAAAAAA);
	Player[playerid][Spawned] = false;

	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		TogglePlayerSpectating(playerid, true);

	SetPlayerTime(playerid, 0, 0);
	SetPlayerInterior(playerid, 0);
	switch (random(3))
	{
		case 0:
		{
			PlayerPlaySound(playerid, 162, 0.0, 0.0, 0.0);
		}
		case 1:
		{
			PlayerPlaySound(playerid, 178, 0.0, 0.0, 0.0);
		}
		case 2:
		{
			PlayerPlaySound(playerid, 176, 0.0, 0.0, 0.0);
		}
	}

	if (!SightseeingInClassSelection)
	{
		switch (random(3))
		{
			case 0:
			{
				InterpolateCameraPos(playerid, MainSpawn[0], MainSpawn[1], MainSpawn[2] + 25.0, MainSpawn[0] - 7.0, MainSpawn[1] + 7.0, MainSpawn[2] + 5.0, 15000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, MainSpawn[0], MainSpawn[1], MainSpawn[2] + 27.0, MainSpawn[0], MainSpawn[1], MainSpawn[2], 7000, CAMERA_MOVE);
			}
			case 1:
			{
				InterpolateCameraPos(
					playerid, MainSpawn[0] + 5.0, MainSpawn[1] + 5.0, MainSpawn[2] + 2.0, MainSpawn[0] - 7.0, MainSpawn[1] + 7.0, MainSpawn[2] + 25.0, 15000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, MainSpawn[0], MainSpawn[1], MainSpawn[2] + 10.0, MainSpawn[0], MainSpawn[1], MainSpawn[2], 7000, CAMERA_MOVE);
			}
			case 2:
			{
				InterpolateCameraPos(
					playerid, MainSpawn[0] + 10.0, MainSpawn[1] - 10.0, MainSpawn[2] + 10.0, MainSpawn[0] - 5.0, MainSpawn[1] + 5.0, MainSpawn[2] + 5.0, 15000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, MainSpawn[0], MainSpawn[1], MainSpawn[2] + 5.0, MainSpawn[0], MainSpawn[1], MainSpawn[2], 10000, CAMERA_MOVE);
			}
		}
	}
	else
	{
		switch (random(7))
		{
			case 0:
			{
				// Vinewood Sign
				InterpolateCameraPos(playerid, 1334.0220, -783.3859, 87.6606, 1407.5430, -896.9464, 87.6606, 20000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, 1415.7408, -806.5591, 85.0399, 1415.7408, -806.5591, 85.0399, 20000, CAMERA_MOVE);
			}
			case 1:
			{
				// Vinewood Sign 2
				InterpolateCameraPos(playerid, 1476.7277, -874.3438, 110.0, 1476.7277, -900.000, 70.0, 5000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, 1415.2177, -807.9233, 200.0, 1415.2177, -807.9233, 85.0623, 5000, CAMERA_MOVE);
			}
			case 2:
			{
				// Desert Mountains
				InterpolateCameraPos(playerid, -365.5211, 1938.2665, 86.0535, -228.2556, 1821.5653, 96.6716, 15000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, -327.0362, 1943.1190, 112.4141, -206.0446, 1895.2479, 91.2241, 15000, CAMERA_MOVE);
			}
			case 3:
			{
				// Streets of San Fierro
				InterpolateCameraPos(playerid, -2078.7246, 731.2352, 69.4141, -1714.5399, 731.2352, 69.4141, 45000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, -1971.8036, 731.0178, 45.2969, -1607.8036, 731.0178, 45.2969, 45000, CAMERA_MOVE);
			}
			case 4:
			{
				// LS Beach
				InterpolateCameraPos(playerid, 340.3344, -1801.2339, 10.6959, 207.3543, -1801.2339, 10.6959, 80000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, 289.9604, -1766.6553, 4.5469, 159.9604, -1766.6553, 4.5469, 80000, CAMERA_MOVE);
			}
			case 5:
			{
				// SF Bridge
				InterpolateCameraPos(playerid, -2630.2266, 1459.0537, 65.6484, -2596.2339, 2039.0321, 263.0035, 20000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, -2678.6890, 1589.8137, 129.3078, -2713.4839, 1757.8318, 98.4932, 20000, CAMERA_MOVE);
			}
			case 6:
			{
				// LV Stadium
				InterpolateCameraPos(playerid, 1328.3080, 2116.9485, 11.0156, 1287.4218, 2097.1223, 55.1216, 20000, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, 1334.9221, 2077.7285, 26.6737, 1381.2794, 2184.0823, 11.0234, 20000, CAMERA_MOVE);
			}
		}
	}
	// Login player
	if (!Player[playerid][Logged])
	{
		new Query[128];
		format(Query, sizeof(Query), "SELECT Name FROM Players WHERE Name = '%q'", Player[playerid][Name]);
		new DBResult: result = db_query(sqliteconnection, Query);

		if (!db_num_rows(result))
		{
			Dialog_ShowCallback(
				playerid, using public InlineRegister<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Registration Dialog", "{FFFFFF}Type your password below to register:",
				"Register", "Leave");
			return db_free_result(result);
		}
		db_free_result(result);
		// Get IP
		new IP[16];
		GetPlayerIp(playerid, IP, sizeof(IP));

		// Construct query to check if the player with the same name and IP has connected before to this server
		format(Query, sizeof(Query), "SELECT * FROM `Players` WHERE `Name` = '%q' AND `IP` = '%q'", Player[playerid][Name], IP);

		// execute
		new DBResult: res = db_query(sqliteconnection, Query);

		// If result returns any registered users with the same name and IP that have connected to this server before, log them in
		if (db_num_rows(res))
		{
			SendClientMessage(playerid, -1, "{009933}Server account: {FFFFFF}automatically logged in!");
			LoginPlayer(playerid, res);
			db_free_result(res);
			new teamid = ShouldPlayerBeReadded(playerid);
			if (teamid != -1)
			{
				SetTimerEx("SpawnConnectedPlayer", 250, false, "ii", playerid, teamid);
			}
			else
			{
				ShowPlayerClassSelection(playerid);
			}
			return 1;
		}
		Dialog_ShowCallback(
			playerid, using public InlineLogin<iiiis>, DIALOG_STYLE_PASSWORD, "{FFFFFF}Login Dialog", "{FFFFFF}Type your password below to log in:", "Login", "Leave");
		return db_free_result(res);
	}

	new teamid = ShouldPlayerBeReadded(playerid);
	if (teamid != -1)
	{
		SetTimerEx("SpawnConnectedPlayer", 250, false, "ii", playerid, teamid);
	}
	else
	{
		ShowPlayerClassSelection(playerid);
	}
	return 1;
}
