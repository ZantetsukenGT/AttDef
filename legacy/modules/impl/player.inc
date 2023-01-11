#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_player
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_player
	#endinput
#endif
#define _attdef_impl_player

/*
	Player related
*/

#include <YSI_Coding\y_hooks>

// Checks player AKAs
GetPlayerAKA(playerid, str[], len)
{
	new IP[16];
	GetPlayerIp(playerid, IP, sizeof(IP));
	new DBResult: dbres = db_query(sqliteconnection, va_return("SELECT `Names` FROM `AKAs` WHERE `IP` = '%q'", IP));

	if (db_num_rows(dbres) > 0)
	{
		db_get_field_assoc(dbres, "Names", str, len);
		return db_free_result(dbres);
	}
	db_free_result(dbres);
	strcat(str, "NULL", len);
	return db_free_result(db_query(sqliteconnection, va_return("INSERT INTO `AKAs` (`IP`, `Names`) VALUES ('%q', '%q')", IP, "")));
}

MatchAKA(playerid)
{
	new AKAString[256];
	GetPlayerAKA(playerid, AKAString, sizeof AKAString);

	new idx;
	do {
		idx = strfind(AKAString, ",", true, idx == 0 ? 0 : idx + 1);
		new compare[MAX_PLAYER_NAME];
		new idx2 = strfind(AKAString, ",", true, idx + 1);
		strmid(compare, AKAString, idx + 1, (idx2 == -1 ? strlen(AKAString) : idx2));

		if (!strcmp(compare, Player[playerid][Name], true) && strlen(Player[playerid][Name]) > 0 && strlen(compare) > 0)
			return 1;
	}
	while (idx != -1);
	return 0;
}

CheckPlayerAKA(playerid)
{
	if (!MatchAKA(playerid))
	{
		new str[16];
		GetPlayerIp(playerid, str, sizeof(str));
		new AKAString[256];
		GetPlayerAKA(playerid, AKAString, sizeof AKAString);
		new add[MAX_PLAYER_NAME + 1];
		format(add, sizeof(add), ",%s", Player[playerid][Name]);

		if (strlen(AKAString) > 0)
			strcat(AKAString, add);
		else
			strcat(AKAString, add[1]);

		new query[128];
		format(query, sizeof(query), "UPDATE `AKAs` SET `Names` = '%q' WHERE `IP` = '%q'", AKAString, str);
		db_free_result(db_query(sqliteconnection, query));
	}
}

// Player name functions
RemoveClanTagFromName(playerid)
{
	new start, end, string[MAX_PLAYER_NAME];
	format(string, MAX_PLAYER_NAME, "%s", Player[playerid][Name]);
	start = strfind(string, "[", true);
	end	  = strfind(string, "]", true);
	if (start >= end)
		return string;

	strdel(string, start, end + 1);
	return string;
}

// Loads nickname and name without the clan tag
InitPlayerNames(playerid)
{
	GetPlayerName(playerid, Player[playerid][Name], MAX_PLAYER_NAME);
	new NewName[MAX_PLAYER_NAME];
	NewName = RemoveClanTagFromName(playerid);

	if (strlen(NewName) != 0)
		Player[playerid][NameWithoutTag] = NewName; // Removes clan tag from the player name and stores the new name in NameWithoutTag variable.
	else
		Player[playerid][NameWithoutTag] = Player[playerid][Name];
}

// Initialize player variables
InitPlayer(playerid)
{
	//added by zyph
	Player[playerid][DmPosX]				   = -1.0;
	Player[playerid][DmPosY]				   = -1.0;
	Player[playerid][DmPosZ]				   = -1.0;
	Player[playerid][DmAngle]				   = -1.0;
	//end added by zyph
	Player[playerid][Level]					   = 0;
	UpdatePlayerAdminGroup(playerid);
	Player[playerid][Weather]				   = MainWeather;
	Player[playerid][Time]					   = MainTime;
	Player[playerid][Team]					   = NON;
	Player[playerid][NetCheckTimeoutTimestamp] = -1;
	Player[playerid][DMReadd]				   = 0;
	Player[playerid][ChatChannel]			   = -1;
	Player[playerid][RoundKills]			   = 0;
	Player[playerid][RoundDeaths]			   = 0;
	Player[playerid][RoundDamage]			   = 0.0;
	Player[playerid][WeaponPicked]			   = 0;
	Player[playerid][TotalKills]			   = 0;
	Player[playerid][TotalDeaths]			   = 0;
	Player[playerid][TotalDamage]			   = 0.0;
	Player[playerid][ACKick]				   = 0;
	Player[playerid][IsSpectatingID]		   = -1;
	Player[playerid][OutOfArena]			   = MAX_ZONE_LIMIT_WARNINGS;
	Player[playerid][FPSKick]				   = 0;
	Player[playerid][PingKick]				   = 0;
	Player[playerid][PacketKick]			   = 0;
	Player[playerid][LastVehicle]			   = 0;
	Player[playerid][TimesSpawned]			   = 0;
	Player[playerid][VWorld]				   = 1;
	Player[playerid][lastChat]				   = GetTickCount();
	Player[playerid][LastAskLeader]			   = 0;
	Player[playerid][LastTimeSynced]		   = GetTickCount();
	Player[playerid][RoundPlayed]			   = 0;
	Player[playerid][shotsHit]				   = 0;
	Player[playerid][TotalBulletsFired]		   = 0;
	Player[playerid][TotalshotsHit]			   = 0;
	Player[playerid][RconTry]				   = 0;
	Player[playerid][NetCheck]				   = true;
	Player[playerid][FPSCheck]				   = true;
	Player[playerid][PingCheck]				   = true;
	Player[playerid][PLCheck]				   = true;
	Player[playerid][SpectatingRound]		   = -1;
	InitPlayerSpectate(playerid);
	ForgetSpectator(playerid);
	Player[playerid][HitSound]			 = 17802;
	Player[playerid][GetHitSound]		 = 1131;
	Player[playerid][LastEditWepLimit]	 = -1;
	Player[playerid][LastEditWeaponSlot] = -1;
	Player[playerid][challengerid]		 = -1;
	Player[playerid][duelweap1]			 = 0;
	Player[playerid][duelweap2]			 = 0;
	Player[playerid][DuelsWon]			 = 0;
	Player[playerid][DuelsLost]			 = 0;
	Player[playerid][LastMsgr]			 = -1;
	Player[playerid][blockedid]			 = -1;
	Player[playerid][FightStyle]		 = 4;
	SetPlayerFightingStyle(playerid, Player[playerid][FightStyle]);
	TargetInfoData[playerid][TargetInfoLastTarget] = INVALID_PLAYER_ID;
	TargetInfoData[playerid][TargetInfoLastTick] = GetTickCount();
	TargetInfoData[playerid][TargetInfoTimer] = 0;
	ChangingSkinOfTeam[playerid]			  = -1;
	Player[playerid][RequestedClass]		  = NON;
	Player[playerid][GunmenuModdingType]	  = 0;
	Player[playerid][GunmenuModdingIndex]	  = 0;
	Player[playerid][RoundTDStyle]			  = 0;

	Player[playerid][Logged]				  = false;
	Player[playerid][IgnoreSpawn]			  = false;
	Player[playerid][InDM]					  = false;
	Player[playerid][InDuel]				  = false;
	Player[playerid][Playing]				  = false;
	Iter_Remove(PlayersInRound, playerid);
	Player[playerid][WasInCP]		   = false;
	Player[playerid][Spectating]	   = false;
	Player[playerid][BeingSpeced]	   = false;
	Player[playerid][WasInBase]		   = false;
	Player[playerid][WasInTeam]		   = NON;
	Player[playerid][TextDrawOnScreen] = false;
	PlayerOnInterface { playerid }	   = false;
	Player[playerid][Spawned]		   = false;
	Player[playerid][IsAFK]			   = false;
	Player[playerid][AskingForHelp]	   = false;
	Player[playerid][Mute]			   = false;
	Player[playerid][ToAddInRound]	   = false;
	InitPlayerInterface(playerid);
	Player[playerid][blockedall]			   = false;
	Player[playerid][OnGunmenu]				   = false;
	Player[playerid][GunmenuStyle]			   = GUNMENU_STYLE_DIALOG;
	Player[playerid][TempNetcheck]			   = false;
	Player[playerid][InDeathCamera]			   = false;
	Player[playerid][HasDeathQuote]			   = false;
	Player[playerid][HadParachuteBeforeFreeze] = false;

	ResetPlayerMoney(playerid);
	SetPlayerColor(playerid, 0xAAAAAAAA);
	RemoveUselessObjectsForPlayer(playerid);
	RemoveBuildingForPlayer(playerid, 1227, 0.0, 0.0, 0.0, 6000.0); // green bin
	RemoveBuildingForPlayer(playerid, 1432, 0.0, 0.0, 0.0, 6000.0); // dining table
	RemoveBuildingForPlayer(playerid, 1281, 0.0, 0.0, 0.0, 6000.0); // dining table 2
	RemoveBuildingForPlayer(playerid, 1594, 0.0, 0.0, 0.0, 6000.0); // chairs && table
	RemoveBuildingForPlayer(playerid, 3374, 0.0, 0.0, 0.0, 6000.0); // arena farm hay
	RemoveBuildingForPlayer(playerid, 3851, 0.0, 0.0, 0.0, 6000.0); //wangcars windows
	RemoveBuildingForPlayer(playerid, 3850, 0.0, 0.0, 0.0, 6000.0); //wangcars windows
	RemoveBuildingForPlayer(playerid, 1265, 0.0, 0.0, 0.0, 6000.0); // trash bag 1
	RemoveBuildingForPlayer(playerid, 1450, 0.0, 0.0, 0.0, 6000.0); // boxes
	RemoveBuildingForPlayer(playerid, 1264, 0.0, 0.0, 0.0, 6000.0); // trash bag 2
	RemoveBuildingForPlayer(playerid, 1280, 0.0, 0.0, 0.0, 6000.0); // bench
	/*RemoveBuildingForPlayer(playerid, 625, 0.0, 0.0, 0.0, 6000.0); // small trees
	RemoveBuildingForPlayer(playerid, 626, 0.0, 0.0, 0.0, 6000.0); 
	RemoveBuildingForPlayer(playerid, 627, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 628, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 629, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 630, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 631, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 632, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 643, 0.0, 0.0, 0.0, 6000.0);*/
	RemoveBuildingForPlayer(playerid, 1649, 0.0, 0.0, 0.0, 6000.0); // small glass
	RemoveBuildingForPlayer(playerid, 3857, 0.0, 0.0, 0.0, 6000.0); // smash glasses
	//RemoveBuildingForPlayer(playerid, 3858, 0.0, 0.0, 0.0, 6000.0);
	//RemoveBuildingForPlayer(playerid, 3859, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1342, 0.0, 0.0, 0.0, 6000.0);		  // stand1
	RemoveBuildingForPlayer(playerid, 1340, 0.0, 0.0, 0.0, 6000.0);		  // stand2
	RemoveBuildingForPlayer(playerid, 1341, 0.0, 0.0, 0.0, 6000.0);		  // stand3
	RemoveBuildingForPlayer(playerid, 1570, 0.0, 0.0, 0.0, 6000.0);		  // stand4
	RemoveBuildingForPlayer(playerid, 1349, 0.0, 0.0, 0.0, 6000.0);		  // shopping cart
	RemoveBuildingForPlayer(playerid, 1408, 0.0, 0.0, 0.0, 6000.0);		  // fence
	RemoveBuildingForPlayer(playerid, 1460, 0.0, 0.0, 0.0, 6000.0);		  // fence2
	RemoveBuildingForPlayer(playerid, 1418, 0.0, 0.0, 0.0, 6000.0);		  // fence3
	RemoveBuildingForPlayer(playerid, 1446, 0.0, 0.0, 0.0, 6000.0);		  // fence4
	RemoveBuildingForPlayer(playerid, 3036, -2176.0, 660.0, 50.0, 200.0); //chinatown gate
	/*RemoveBuildingForPlayer(playerid, 726, 819.0, -1527.0, 13.0, 75.0); // base 207 object
	RemoveBuildingForPlayer(playerid, 789, 819.0, -1527.0, 13.0, 75.0); // base 207 object
	RemoveBuildingForPlayer(playerid, 803, 819.0, -1527.0, 13.0, 75.0); // base 207 object
	RemoveBuildingForPlayer(playerid, 805, 819.0, -1527.0, 13.0, 75.0); // base 207 object
	RemoveBuildingForPlayer(playerid, 762, 819.0, -1527.0, 13.0, 75.0); // base 207 object
	RemoveBuildingForPlayer(playerid, 800, 819.0, -1527.0, 13.0, 75.0); // base 207 object
	RemoveBuildingForPlayer(playerid, 789, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 803, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 805, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 762, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 800, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 711, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 3506, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 712, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 645, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 800, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 647, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 713, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 782, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 789, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 16390, 965, 1737, 8.0, 500.0); // base 229 object
	RemoveBuildingForPlayer(playerid, 5636, 2062, -1385, 23, 100.0); // base 233 object
	RemoveBuildingForPlayer(playerid, 642, 1568, -1892, 13, 50.0); // custom base umbrella
	RemoveBuildingForPlayer(playerid, 1479, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 626, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 638, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 628, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 1480, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 627, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 1458, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 640, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 625, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 1418, -2563, 323, 10, 80.0); // gardening base
	RemoveBuildingForPlayer(playerid, 741, -2563, 323, 10, 80.0); // gardening base*/
	RemoveBuildingForPlayer(playerid, 5464, 1902, -1309, 29, 200.0); // jeff constr

	LoadPlayerTextDraws(playerid);

	for (new i = 0; i < MAX_PLAYER_BARS; i++) TeamBarShownForPlayer[playerid] [_:i] = false;

	ShowTeamCornerInfo(playerid);

	CreatePlayerLabels(playerid);
	Player[playerid][DamageBubbleTick] = 0;

	InitPlayerMessageBox(playerid);
	InitPlayerNames(playerid);
	InitPlayerWeaponBind(playerid);
	InitPlayerVisualDamage(playerid);
	InitPlayerVoting(playerid);

	noclipdata[playerid][cameramode]	= CAMERA_MODE_NONE;
	noclipdata[playerid][lrold]			= 0;
	noclipdata[playerid][udold]			= 0;
	noclipdata[playerid][noclipcammode] = 0;
	noclipdata[playerid][lastmove]		= GetTickCount();
	noclipdata[playerid][accelmul]		= 0.0;
	noclipdata[playerid][FlyMode]		= false;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerLabels(playerid);
	Iter_Remove(PlayersInVehicles, playerid);
	return 1;
}

CreatePlayerLabels(playerid)
{
	Player[playerid][InfoLabel] = Create3DTextLabel(" ", -1, 0, 0, 0, DRAW_DISTANCE - 3.2, 0, true);
	Attach3DTextLabelToPlayer(Player[playerid][InfoLabel], playerid, 0, 0, -0.7);

	Player[playerid][DamageLabel] = Create3DTextLabel(" ", -1, 0, 0, 0, DRAW_DISTANCE - 3.2, 0, true);
	Attach3DTextLabelToPlayer(Player[playerid][DamageLabel], playerid, 0, 0, 2.0);
}

DestroyPlayerLabels(playerid)
{
	Delete3DTextLabel(Player[playerid][InfoLabel]);
	Delete3DTextLabel(Player[playerid][DamageLabel]);
}

LoginPlayer(playerid, DBResult: res)
{
	new iString[128];

	// Load level
	db_get_field_assoc(res, "Level", iString, sizeof(iString));
	Player[playerid][Level] = strval(iString);
	UpdatePlayerAdminGroup(playerid);

	// Load Weather
	db_get_field_assoc(res, "Weather", iString, sizeof(iString));
	Player[playerid][Weather] = strval(iString);

	// Load time
	db_get_field_assoc(res, "Time", iString, sizeof(iString));
	Player[playerid][Time] = strval(iString);

	// Load ChatChannel
	db_get_field_assoc(res, "ChatChannel", iString, sizeof(iString));
	Player[playerid][ChatChannel] = strval(iString);

	// Load NetCheck
	db_get_field_assoc(res, "NetCheck", iString, sizeof(iString));
	Player[playerid][NetCheck] = bool: strval(iString);

	// Load HitSound
	db_get_field_assoc(res, "HitSound", iString, sizeof(iString));
	Player[playerid][HitSound] = strval(iString);

	// Load GetHitSound
	db_get_field_assoc(res, "GetHitSound", iString, sizeof(iString));
	Player[playerid][GetHitSound] = strval(iString);

	// Load Duels won
	db_get_field_assoc(res, "DWon", iString, sizeof(iString));
	Player[playerid][DuelsWon] = strval(iString);

	// Load Duels Lost
	db_get_field_assoc(res, "DLost", iString, sizeof(iString));
	Player[playerid][DuelsLost] = strval(iString);

	// Load ShowSpecs
	db_get_field_assoc(res, "InterfaceSpec", iString, sizeof(iString));
	PlayerInterface[playerid][INTERFACE_SPEC] = strval(iString) != 0;

	// Load Fighting Style
	db_get_field_assoc(res, "FightStyle", iString, sizeof(iString));
	Player[playerid][FightStyle] = strval(iString);
	SetPlayerFightingStyle(playerid, Player[playerid][FightStyle]);

	// Load Death Messages
	db_get_field_assoc(res, "DeathMessage", iString, sizeof(iString));
	DeathMessageStr[playerid][0] = EOS;
	strcat(DeathMessageStr[playerid], iString, 64);
	if (strcmp("NO_DEATH_MESSAGE", DeathMessageStr[playerid], false) != 0)
		Player[playerid][HasDeathQuote] = true;

	// Load Show net textdraws
	db_get_field_assoc(res, "InterfaceNet", iString, sizeof(iString));
	PlayerInterface[playerid][INTERFACE_NET] = strval(iString) != 0;

	// Load weapon key binds
	new fieldName[12], value;
	for (new i = 0; i < MAX_WEAPON_BINDS; i++)
	{
		format(fieldName, sizeof fieldName, "WeaponBind%d", i);
		db_get_field_assoc(res, fieldName, iString, sizeof(iString));
		value = strval(iString);
		if (value != -1)
			WeaponBindData[playerid][BindKeyWeapon][i] = value;
	}

	// Load Gunmenu Style
	db_get_field_assoc(res, "GunmenuStyle", iString, sizeof(iString));
	Player[playerid][GunmenuStyle] = strval(iString);

	// Load Weapon Binding
	db_get_field_assoc(res, "WeaponBinding", iString, sizeof(iString));
	Player[playerid][WeaponBinding] = strval(iString) != 0;

	// Load player markers setting
	db_get_field_assoc(res, "PlayerMarkers", iString, sizeof(iString));
	Player[playerid][PlayerMarkers] = strval(iString) != 0;

	// Load round textdraws style
	db_get_field_assoc(res, "RoundTDStyle", iString, sizeof(iString));
	Player[playerid][RoundTDStyle] = strval(iString);

	// Get current IP address
	new IP[16];
	GetPlayerIp(playerid, IP, sizeof(IP));

	// Update players table with new IP address for auto login if they reconnect.
	format(iString, sizeof(iString), "UPDATE `Players` SET `IP` = '%q' WHERE `Name` = '%q' AND IP != '%q'", IP, Player[playerid][Name], IP);
	db_free_result(db_query(sqliteconnection, iString));

	// Update last seen/logged in
	new day, month, year;
	getdate(year, month, day);
	format(
		iString, sizeof(iString), "UPDATE `Players` SET `LastSeen_Day` = %d, `LastSeen_Month` = %d, `LastSeen_Year` = %d WHERE `Name` = '%q'", day, month, year,
		Player[playerid][Name]);
	db_free_result(db_query(sqliteconnection, iString));

	Player[playerid][Logged] = true;
}

StorePlayerVariablesMin(playerid)
{
	for (new i = 0; i < SAVE_SLOTS; i++)
	{
		if (strlen(SaveVariables[i][pName]) >= 2)
			continue;

		SaveVariables[i][pTeam]		 = Player[playerid][Team];
		SaveVariables[i][RKills]	 = Player[playerid][RoundKills];
		SaveVariables[i][RDeaths]	 = Player[playerid][RoundDeaths];
		SaveVariables[i][RDamage]	 = Player[playerid][RoundDamage];
		SaveVariables[i][TKills]	 = Player[playerid][TotalKills];
		SaveVariables[i][TDeaths]	 = Player[playerid][TotalDeaths];
		SaveVariables[i][TDamage]	 = Player[playerid][TotalDamage];
		SaveVariables[i][TPlayed]	 = Player[playerid][RoundPlayed];
		SaveVariables[i][sWasInBase] = Player[playerid][WasInBase];

		OnPlayerAmmoUpdate(playerid);
		SaveVariables[i][iAccuracy]	   = floatround(Player[playerid][Accuracy], floatround_round);
		SaveVariables[i][tshotsHit]	   = Player[playerid][TotalshotsHit];
		SaveVariables[i][tBulletsShot] = Player[playerid][TotalBulletsFired];

		SaveVariables[i][gHealth]	   = 0;
		SaveVariables[i][gArmour]	   = 0;

		SaveVariables[i][RoundID]	   = Current;
		SaveVariables[i][ToBeAdded]	   = false;
		SaveVariables[i][CheckScore]   = true;

		new weapID, weapAmmo = 0;
		GetPlayerWeaponData(playerid, 8, weapID, weapAmmo);
		if (weapID == WEAPON_GRENADE)
			SaveVariables[i][SavedGrenadeAmmo] = weapAmmo;
		else
			SaveVariables[i][SavedGrenadeAmmo] = 0;

		format(SaveVariables[i][pName], 24, Player[playerid][Name]);
		format(SaveVariables[i][pNameWithoutTag], 24, Player[playerid][NameWithoutTag]);

		if (GetPlayerWeapon(playerid) == WEAPON_PARACHUTE)
			SaveVariables[i][HadParachute] = 1;
		else
			SaveVariables[i][HadParachute] = 0;

		if (IsPlayerInAnyVehicle(playerid))
		{
			SaveVariables[i][pVehicleID] = GetPlayerVehicleID(playerid);
			SaveVariables[i][pSeatID]	 = GetPlayerVehicleSeat(playerid);
		}
		else
		{
			SaveVariables[i][pVehicleID] = -1;
			SaveVariables[i][pSeatID]	 = -1;
		}
		break;
	}
	return 1;
}

StorePlayerVariables(playerid)
{
	new iString[128];
	for (new i = 0; i < SAVE_SLOTS; i++)
	{
		if (strlen(SaveVariables[i][pName]) >= 2)
			continue;

		format(SaveVariables[i][pName], 24, Player[playerid][Name]);
		format(SaveVariables[i][pNameWithoutTag], 24, Player[playerid][NameWithoutTag]);

		GetPlayerPos(playerid, SaveVariables[i][pCoords][0], SaveVariables[i][pCoords][1], SaveVariables[i][pCoords][2]);
		GetPlayerFacingAngle(playerid, SaveVariables[i][pCoords][3]);

		if (!Player[i][ToAddInRound])
		{
			SaveVariables[i][gHealth] = GetHP(playerid);
			SaveVariables[i][gArmour] = GetAP(playerid);
		}
		else
		{
			SaveVariables[i][gArmour] = 100;
			SaveVariables[i][gHealth] = 100;
		}

		SaveVariables[i][pTeam]		 = Player[playerid][Team];
		SaveVariables[i][pInterior]	 = GetPlayerInterior(playerid);
		SaveVariables[i][pVWorld]	 = GetPlayerVirtualWorld(playerid);

		SaveVariables[i][RKills]	 = Player[playerid][RoundKills];
		SaveVariables[i][RDeaths]	 = Player[playerid][RoundDeaths];
		SaveVariables[i][RDamage]	 = Player[playerid][RoundDamage];
		SaveVariables[i][TKills]	 = Player[playerid][TotalKills];
		SaveVariables[i][TDeaths]	 = Player[playerid][TotalDeaths];
		SaveVariables[i][TDamage]	 = Player[playerid][TotalDamage];
		SaveVariables[i][TPlayed]	 = Player[playerid][RoundPlayed];
		SaveVariables[i][sWasInBase] = Player[playerid][WasInBase];

		OnPlayerAmmoUpdate(playerid);
		SaveVariables[i][iAccuracy]	   = floatround(Player[playerid][Accuracy], floatround_round);
		SaveVariables[i][tshotsHit]	   = Player[playerid][TotalshotsHit];
		SaveVariables[i][tBulletsShot] = Player[playerid][TotalBulletsFired];

		for (new j = 0; j < MAX_GUNMENU_GUNS; j++) { SaveVariables[i][HadGunmenuGun][j] = GunmenuData[j][HasGun][playerid]; }

		SaveVariables[i][RoundID]	 = Current;
		SaveVariables[i][ToBeAdded]	 = true;
		SaveVariables[i][CheckScore] = true;

		new weapID, weapAmmo = 0;
		GetPlayerWeaponData(playerid, 8, weapID, weapAmmo);
		if (weapID == WEAPON_GRENADE)
			SaveVariables[i][SavedGrenadeAmmo] = weapAmmo;
		else
			SaveVariables[i][SavedGrenadeAmmo] = 0;

		if (GetPlayerWeapon(playerid) == WEAPON_PARACHUTE)
			SaveVariables[i][HadParachute] = 1;
		else
			SaveVariables[i][HadParachute] = 0;

		if (IsPlayerInAnyVehicle(playerid))
		{
			SaveVariables[i][pVehicleID] = GetPlayerVehicleID(playerid);
			SaveVariables[i][pSeatID]	 = GetPlayerVehicleSeat(playerid);
		}
		else
		{
			SaveVariables[i][pVehicleID] = -1;
			SaveVariables[i][pSeatID]	 = -1;
		}

		if (Current != -1 && (!AllowStartBase || ElapsedTime < 20) && (Player[i][ToAddInRound] || Player[i][Playing]))
			SaveVariables[i][WasCrashedInStart] = true;

		format(iString, sizeof(iString), "{FFFFFF}%s's " COL_PRIM "data saved.", Player[playerid][Name]);
		SendClientMessageToAll(-1, iString);
		break;
	}
}

// Note: this function returns team id if the player is supposed to be re-added to round, otherwise -1
ShouldPlayerBeReadded(playerid)
{
	for (new i = 0; i < SAVE_SLOTS; i++)
	{
		if (strlen(SaveVariables[i][pName]) >= 2 && strcmp(SaveVariables[i][pName], Player[playerid][Name], true) == 0)
		{
			if (SaveVariables[i][RoundID] != Current || Current == -1 || !SaveVariables[i][ToBeAdded])
				return -1;
			else
				return SaveVariables[i][pTeam];
		}
	}
	return -1;
}

LoadPlayerVariables(playerid)
{
	new iString[160];

	for (new i = 0; i < SAVE_SLOTS; i++)
	{
		if (strlen(SaveVariables[i][pName]) >= 2 && strcmp(SaveVariables[i][pName], Player[playerid][Name], true) == 0)
		{
			if (SaveVariables[i][RoundID] != Current || Current == -1)
			{
				Player[playerid][TotalKills]		= SaveVariables[i][TKills];
				Player[playerid][TotalDeaths]		= SaveVariables[i][TDeaths];
				Player[playerid][TotalDamage]		= SaveVariables[i][TDamage];
				Player[playerid][RoundPlayed]		= SaveVariables[i][TPlayed];
				Player[playerid][Accuracy]			= SaveVariables[i][iAccuracy];
				Player[playerid][TotalshotsHit]		= SaveVariables[i][tshotsHit];
				Player[playerid][TotalBulletsFired] = SaveVariables[i][tBulletsShot];

				ResetSaveVariables(i);

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has spawned as: {FFFFFF}%s", Player[playerid][Name], TeamName[Player[playerid][Team]]);
				SendClientMessageToAll(-1, iString);

				UpdateRoundKillDmgTDmg(playerid);
				return 1;
			}
			else if (!SaveVariables[i][ToBeAdded])
			{
				Player[playerid][TotalKills]		= SaveVariables[i][TKills];
				Player[playerid][TotalDeaths]		= SaveVariables[i][TDeaths];
				Player[playerid][TotalDamage]		= SaveVariables[i][TDamage];
				Player[playerid][RoundPlayed]		= SaveVariables[i][TPlayed];
				Player[playerid][Accuracy]			= SaveVariables[i][iAccuracy];
				Player[playerid][TotalshotsHit]		= SaveVariables[i][tshotsHit];
				Player[playerid][TotalBulletsFired] = SaveVariables[i][tBulletsShot];
				Player[playerid][RoundKills]		= SaveVariables[i][RKills];
				Player[playerid][RoundDeaths]		= SaveVariables[i][RDeaths];
				Player[playerid][RoundDamage]		= SaveVariables[i][RDamage];
				Player[playerid][WasInBase]			= SaveVariables[i][sWasInBase];

				ResetSaveVariables(i);

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has spawned as: {FFFFFF}%s", Player[playerid][Name], TeamName[Player[playerid][Team]]);
				SendClientMessageToAll(-1, iString);

				UpdateRoundKillDmgTDmg(playerid);
				return 1;
			}

			Player[playerid][Playing]	= true;
			Player[playerid][WasInBase] = true;
			Iter_Add(PlayersInRound, playerid);

			Player[playerid][Team]				= SaveVariables[i][pTeam];
			Player[playerid][WasInTeam]			= Player[playerid][Team];

			Player[playerid][RoundKills]		= SaveVariables[i][RKills];
			Player[playerid][RoundDeaths]		= SaveVariables[i][RDeaths];
			Player[playerid][RoundDamage]		= SaveVariables[i][RDamage];
			Player[playerid][TotalKills]		= SaveVariables[i][TKills];
			Player[playerid][TotalDeaths]		= SaveVariables[i][TDeaths];
			Player[playerid][TotalDamage]		= SaveVariables[i][TDamage];
			Player[playerid][RoundPlayed]		= SaveVariables[i][TPlayed];
			Player[playerid][Accuracy]			= SaveVariables[i][iAccuracy];
			Player[playerid][TotalshotsHit]		= SaveVariables[i][tshotsHit];
			Player[playerid][TotalBulletsFired] = SaveVariables[i][tBulletsShot];

			if (!SaveVariables[i][WasCrashedInStart])
			{
				SetSpawnInfo(
					playerid, Player[playerid][Team], Skin[Player[playerid][Team]], SaveVariables[i][pCoords][0], SaveVariables[i][pCoords][1], SaveVariables[i][pCoords][2] + 1,
					SaveVariables[i][pCoords][3], 0, 0, 0, 0, 0, 0);

				SetPlayerInterior(playerid, SaveVariables[i][pInterior]);
				SetPlayerVirtualWorld(playerid, SaveVariables[i][pVWorld]);
			}
			else if (Current != -1)
			{
				if (GameType == BASE)
				{
					switch (Player[playerid][Team])
					{
						case ATTACKER:
							SetSpawnInfo(
								playerid, Player[playerid][Team], Skin[Player[playerid][Team]], BAttackerSpawn[Current][0] + RandomMinMax(-3, 3), BAttackerSpawn[Current][1] + RandomMinMax(-3, 3),
								BAttackerSpawn[Current][2] + 0.5, 0, 0, 0, 0, 0, 0, 0);
						case DEFENDER:
							SetSpawnInfo(
								playerid, Player[playerid][Team], Skin[Player[playerid][Team]], BDefenderSpawn[Current][0] + RandomMinMax(-3, 3), BDefenderSpawn[Current][1] + RandomMinMax(-3, 3),
								BDefenderSpawn[Current][2] + 0.5, 0, 0, 0, 0, 0, 0, 0);
					}
					SetPlayerInterior(playerid, BInterior[Current]);
				}
				else if (GameType == ARENA)
				{
					switch (Player[playerid][Team])
					{
						case ATTACKER:
							SetSpawnInfo(
								playerid, Player[playerid][Team], Skin[Player[playerid][Team]], AAttackerSpawn[Current][0] + RandomMinMax(-3, 3), AAttackerSpawn[Current][1] + RandomMinMax(-3, 3),
								AAttackerSpawn[Current][2] + 0.5, 0, 0, 0, 0, 0, 0, 0);
						case DEFENDER:
							SetSpawnInfo(
								playerid, Player[playerid][Team], Skin[Player[playerid][Team]], ADefenderSpawn[Current][0] + RandomMinMax(-3, 3), ADefenderSpawn[Current][1] + RandomMinMax(-3, 3),
								ADefenderSpawn[Current][2] + 0.5, 0, 0, 0, 0, 0, 0, 0);
					}
					SetPlayerInterior(playerid, AInterior[Current]);
				}
				SetPlayerVirtualWorld(playerid, 2);
			}

			Player[playerid][IgnoreSpawn] = true;
			SpawnPlayer(playerid);

			ShowTeamBarsForPlayer(playerid);
			CreatePlayerTeamBar(playerid);

			ShowTeamCornerInfo(playerid);
			UpdateTeamCornerInfo();

			UpdateTeamPlayerCount(Player[playerid][Team], false);
			SetHP(playerid, SaveVariables[i][gHealth]);
			SetAP(playerid, SaveVariables[i][gArmour]);
			UpdateTeamHP(Player[playerid][Team]);

			ColorFix(playerid);
			SetPlayerTeam(playerid, NO_TEAM);
			RadarFix();
			SetCPForPlayer(playerid);

			if (GameType == BASE)
			{
				new team = Player[playerid][Team];
				new ct	 = 0;
				for (new j = 0; j < MAX_GUNMENU_GUNS; j++)
				{
					if (SaveVariables[i][HadGunmenuGun][j])
					{
						if (GunmenuData[j][TimesSelected][team] == GunmenuData[j][GunLimit])
						{
							ct = -1;
							ResetPlayerGunmenu(playerid, false);
							ShowPlayerGunmenu(playerid, 500);
							SendErrorMessage(
								playerid, va_return("This weapon is no longer available because limit has exceeded. [%d/%d]", GunmenuData[j][GunLimit], GunmenuData[j][GunLimit]));
							break;
						}
						else
						{
							ct++;
							GivePlayerWeapon(playerid, GunmenuData[j][GunID], GunmenuData[j][GunAmmo]);
							GunmenuData[j][HasGun][playerid] = true;
							GunmenuData[j][TimesSelected][team]--;
						}
					}
				}
				if (ct == 0)
				{
					ResetPlayerGunmenu(playerid, false);
					ShowPlayerGunmenu(playerid, 500);
				}
				if (SaveVariables[i][HadParachute] == 1)
				{
					GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);
					SetPlayerArmedWeapon(playerid, WEAPON_PARACHUTE);
				}
				else
					SetPlayerArmedWeapon(playerid, 0);

				if (SaveVariables[i][pVehicleID] != -1)
					SetTimerEx("RespawnInVehicleAfterComeBack", 500, false, "ddd", playerid, SaveVariables[i][pVehicleID], SaveVariables[i][pSeatID]);
			}
			else if (GameType == ARENA)
			{
				new team = Player[playerid][Team];
				for (new j = 0; j < MAX_GUNMENU_GUNS; j++)
				{
					if (SaveVariables[i][HadGunmenuGun][j])
					{
						GivePlayerWeapon(playerid, GunmenuData[j][GunID], GunmenuData[j][GunAmmo]);
						GunmenuData[j][HasGun][playerid] = true;
						GunmenuData[j][TimesSelected][team]--;
					}
				}
				GangZoneShowForPlayer(playerid, ArenaZone, GANGZONE_ARENA);
			}
			if (RoundPaused)
			{
				TogglePlayerControllable(playerid, 0);
				TextDrawShowForAll(PauseTD);
			}
			else
				TogglePlayerControllable(playerid, 1);

			format(iString, sizeof(iString), "" COL_PRIM "Re-added player {FFFFFF}%s. " COL_PRIM "Data fetched successfully.", Player[playerid][Name]);
			SendClientMessageToAll(-1, iString);

			if (!Player[playerid][FakePacketRenovation] && Player[playerid][NetCheck] && NetStats_GetConnectedTime(playerid) < 300000)
			{
				SetTimerEx("FakePacketRenovationEnd", 30000, false, "ifb", playerid, NetStats_PacketLossPercent(playerid), false);
				Player[playerid][FakePacketRenovation] = true;
			}

			UpdateRoundKillDmgTDmg(playerid);

			SaveVariables[i][PauseWait] = false;

			ResetSaveVariables(i);
			return 1;
		}
	}
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has spawned as: {FFFFFF}%s", Player[playerid][Name], TeamName[Player[playerid][Team]]);
	SendClientMessageToAll(-1, iString);
	return 1;
}

ResetSaveVariables(index)
{
	SaveVariables[index][pName][0] = EOS;

	SaveVariables[index][pCoords][0]		= 0.0;
	SaveVariables[index][pCoords][1]		= 0.0;
	SaveVariables[index][pCoords][2]		= 0.0;
	SaveVariables[index][pCoords][3]		= 0.0;

	SaveVariables[index][gHealth]			= 0;
	SaveVariables[index][gArmour]			= 0;
	SaveVariables[index][pInterior]			= 0;
	SaveVariables[index][pVWorld]			= 0;
	SaveVariables[index][pTeam]				= 0;
	SaveVariables[index][RKills]			= 0;
	SaveVariables[index][RDeaths]			= 0;
	SaveVariables[index][RDamage]			= 0.0;
	SaveVariables[index][TKills]			= 0;
	SaveVariables[index][TDeaths]			= 0;
	SaveVariables[index][TDamage]			= 0.0;
	SaveVariables[index][sWasInBase]		= false;
	SaveVariables[index][RoundID]			= -1;
	SaveVariables[index][WasCrashedInStart] = false;
	SaveVariables[index][ToBeAdded]			= false;
	SaveVariables[index][CheckScore]		= false;
	SaveVariables[index][PauseWait]			= false;
	SaveVariables[index][pVehicleID]		= -1;
	SaveVariables[index][pSeatID]			= -1;
	SaveVariables[index][HadParachute]		= 0;
	SaveVariables[index][SavedGrenadeAmmo]	= 0;
	for (new i = 0; i < MAX_GUNMENU_GUNS; i++) SaveVariables[index][HadGunmenuGun][i] = false;
}

ClearPlayerVariables()
{
	for (new i = 0; i < SAVE_SLOTS; i++) { ResetSaveVariables(i); }
}
