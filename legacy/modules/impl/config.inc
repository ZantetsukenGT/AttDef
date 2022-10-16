#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_config
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_config
	#endinput
#endif
#define _attdef_impl_config

/*
	Gamemode configuration
*/

// Functions
ShowConfigDialog(playerid1)
{
	inline InlineConfig(playerid, dialogid, response, listitem, string: inputtext[])
	{
#pragma unused dialogid, inputtext
		if (!response)
			return 1;
		switch (listitem)
		{
			case 0:
			{
				ShowPlayerDialog(
					playerid, DIALOG_ATT_NAME, DIALOG_STYLE_INPUT, COL_PRIM "Attacker Team Name", COL_PRIM "Enter {FFFFFF}Attacker " COL_PRIM "Team Name Below:", "Next", "Close");
			}
			case 1:
			{
				new iString[128];
				format(iString, sizeof(iString), "%sAttacker Team\n%sDefender Team\n%sReferee Team", TextColor[ATTACKER], TextColor[DEFENDER], TextColor[REFEREE]);
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_TEAM_SKIN, DIALOG_STYLE_LIST, COL_PRIM "Select team", iString, "OK", "Back");
			}
			case 2:
			{
				ShowPlayerDialog(
					playerid, DIALOG_CONFIG_SET_AAD, DIALOG_STYLE_LIST, COL_PRIM "A/D Config", COL_PRIM "Health\n" COL_PRIM "Armour\n" COL_PRIM "Round Time\n" COL_PRIM "CP Time",
					"OK", "Back");
			}
			case 3:
			{
				SendRconCommand("gmx");
			}
			case 4:
			{
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_MAX_PING, DIALOG_STYLE_INPUT, COL_PRIM "Set max ping", "Set the max ping:", "OK", "Back");
			}
			case 5:
			{
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_MAX_PACKET, DIALOG_STYLE_INPUT, COL_PRIM "Set max packetloss", "Set the max packetloss:", "OK", "Back");
			}
			case 6:
			{
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_MIN_FPS, DIALOG_STYLE_INPUT, COL_PRIM "Set minimum FPS", "Set the minimum FPS:", "OK", "Back");
			}
			case 7:
			{
				new string[144];
				strcat(string, strlen(GroupAccessPassword[0]) > 0 ? "{FF6666}" : "{66FF66}");
				strcat(string, TeamName[ATTACKER]);

				strcat(string, strlen(GroupAccessPassword[1]) > 0 ? "\n{FF6666}" : "\n{66FF66}");
				strcat(string, TeamName[DEFENDER]);

				strcat(string, strlen(GroupAccessPassword[2]) > 0 ? "\n{FF6666}Referee" : "\n{66FF66}Referee");

				strcat(string, strlen(GroupAccessPassword[3]) > 0 ? "\n{FF6666}" : "\n{66FF66}");
				strcat(string, TeamName[ATTACKER]);
				strcat(string, " Sub");

				strcat(string, strlen(GroupAccessPassword[4]) > 0 ? "\n{FF6666}" : "\n{66FF66}");
				strcat(string, TeamName[DEFENDER]);
				strcat(string, " Sub");
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_GA, DIALOG_STYLE_LIST, COL_PRIM "Config Settings", string, "OK", "Cancel");
				return 1;
			}
			case 8:
			{
				if (!ServerLocked)
				{
					ShowPlayerDialog(playerid, DIALOG_SERVER_PASS, DIALOG_STYLE_INPUT, COL_PRIM "Server Password", COL_PRIM "Enter server password below:", "Ok", "Close");
				}
				else
				{
					SendRconCommand("password 0");
					ServerLocked = false;
					PermLocked	 = false;
				}
			}
			case 9:
			{
				AntiSpam = !AntiSpam;
				va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}anti-spam" COL_PRIM ".", Player[playerid][Name], AntiSpam ? "{66FF66}enabled" : "{FF6666}disabled");

				ShowConfigDialog(playerid);
			}
			case 10:
			{
				AutoBal = !AutoBal;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}auto-balance " COL_PRIM "in non war mode.", Player[playerid][Name], AutoBal ? "{66FF66}enabled" : "{FF6666}disabled");

				ShowConfigDialog(playerid);
			}
			case 11:
			{
				AutoPause = !AutoPause;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Auto-Pause " COL_PRIM "on player disconnect in war mode.", Player[playerid][Name],
					AutoPause ? "{66FF66}enabled" : "{FF6666}disabled");

				ShowConfigDialog(playerid);
			}
			case 12:
			{
				LobbyGuns = !LobbyGuns;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}guns in lobby" COL_PRIM ".", Player[playerid][Name], LobbyGuns ? "{66FF66}enabled" : "{FF6666}disabled");

				ShowConfigDialog(playerid);
			}
			case 13:
			{
				if (Current != -1)
					return SendErrorMessage(playerid, "Can't use this while a round is in progress.");

				CPInArena = !CPInArena;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Checkpoint in arena " COL_PRIM "option.", Player[playerid][Name], CPInArena ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'CPInArena'", CPInArena)));
				ShowConfigDialog(playerid);
			}
			case 14:
			{
				AntiMacros = !AntiMacros;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Anti-macros " COL_PRIM "system.", Player[playerid][Name], AntiMacros ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'AntiMacros'", AntiMacros)));
				ShowConfigDialog(playerid);
			}
			case 15:
			{
				DeadBodies = !DeadBodies;
				if (!DeadBodies)
					DeleteAllDeadBodies();
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Dead bodies " COL_PRIM "option.", Player[playerid][Name], DeadBodies ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'DeadBodies'", DeadBodies)));
				ShowConfigDialog(playerid);
			}
			case 16:
			{
				DeathCamera = !DeathCamera;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Death camera " COL_PRIM "system.", Player[playerid][Name], DeathCamera ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'DeathCamera'", DeathCamera)));
				ShowConfigDialog(playerid);
			}
			case 17:
			{
				if (Current != -1)
					return SendErrorMessage(playerid, "Can't do this while a round is in progress.");

				ShowHPBars = !ShowHPBars;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}HP Bars " COL_PRIM "system.", Player[playerid][Name], ShowHPBars ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'ShowHPBars'", ShowHPBars)));
				ShowConfigDialog(playerid);
			}
			case 18:
			{
				GunmenuRestrictions = !GunmenuRestrictions;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Gunmenu restrictions" COL_PRIM ".", Player[playerid][Name], GunmenuRestrictions ? "{66FF66}enabled" : "{FF6666}disabled");

				ShowConfigDialog(playerid);
			}
			case 19:
			{
				MeleeAllowed = !MeleeAllowed;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}melee weapons menu " COL_PRIM "option.", Player[playerid][Name], MeleeAllowed ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'MeleeAllowed'", MeleeAllowed)));
				ShowConfigDialog(playerid);
			}
			case 20:
			{
				AutoRoundStarter = !AutoRoundStarter;
				if (AutoRoundStarter && Current == -1 && AllowStartBase)
					SetRoundAutoStart(0);
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}auto round start " COL_PRIM "option.", Player[playerid][Name], AutoRoundStarter ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'AutoRoundStarter'", AutoRoundStarter)));
				ShowConfigDialog(playerid);
			}
			case 21:
			{
				RandomDeathMessages = !RandomDeathMessages;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Random Death Messages" COL_PRIM ".", Player[playerid][Name], RandomDeathMessages ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'RDeathMsg'", RandomDeathMessages)));
				ShowConfigDialog(playerid);
			}
			case 22:
			{
				SightseeingInClassSelection = !SightseeingInClassSelection;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Sightseeing In Class Selection" COL_PRIM ".", Player[playerid][Name],
					SightseeingInClassSelection ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'SightseeingInCS'", SightseeingInClassSelection)));
				ShowConfigDialog(playerid);
			}
			case 23:
			{
				VehicleHealthTextdraw = !VehicleHealthTextdraw;
				if (VehicleHealthTextdraw)
				{
					foreach (new i : Player)
					{
						if (IsPlayerInAnyVehicle(i))
						{
							PlayerTextDrawSetString(i, VInfo[i], "_");
							PlayerTextDrawShow(i, VInfo[i]);
						}
					}
				}
				else
				{
					foreach (new i : Player)
					{
						if (IsPlayerInAnyVehicle(i))
							PlayerTextDrawHide(i, VInfo[i]);
					}
				}
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Vehicle Health Information" COL_PRIM ".", Player[playerid][Name],
					VehicleHealthTextdraw ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'VehicleHealthTD'", VehicleHealthTextdraw)));
				ShowConfigDialog(playerid);
			}
			case 24:
			{
				SyncAbuse = !SyncAbuse;
				va_SendClientMessageToAll(-1, "%s " COL_PRIM "has %s {FFFFFF}Sync Abuse" COL_PRIM ".", Player[playerid][Name], SyncAbuse ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'SyncAbuse'", SyncAbuse)));
				ShowConfigDialog(playerid);
			}
			case 25:
			{
				ScreenFlashing = !ScreenFlashing;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}Screen Flashing" COL_PRIM ".", Player[playerid][Name], ScreenFlashing ? "{66FF66}enabled" : "{FF6666}disabled");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'ScreenFlash'", ScreenFlashing)));
				ShowConfigDialog(playerid);
			}
			case 26:
			{
				DefendersWithVehicles = !DefendersWithVehicles;
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has %s {FFFFFF}defenders to use vehicles" COL_PRIM ".", Player[playerid][Name],
					DefendersWithVehicles ? "{66FF66}allowed" : "{FF6666}disallowed");

				db_free_result(db_query(sqliteconnection, va_return("UPDATE Configs SET Value = %d WHERE Option = 'DefVehicles'", DefendersWithVehicles)));
				ShowConfigDialog(playerid);
			}
		}
		return 1;
	}

	new string[1024];
	strcat(string, COL_PRIM "Team Names");
	strcat(string, "\n" COL_PRIM "Team Skins");
	strcat(string, "\n" COL_PRIM "A/D Settings");
	strcat(string, "\n" COL_PRIM "Restart Server");
	strcat(string, "\n" COL_PRIM "Max Ping");
	strcat(string, "\n" COL_PRIM "Max Packetloss");
	strcat(string, "\n" COL_PRIM "Min FPS");

	new bool: isrestricted;
	for (new i = 0; i < sizeof(GroupAccessPassword); i++)
	{
		if (strlen(GroupAccessPassword[i]) == 0)
			continue;
		isrestricted = true;
		break;
	}
	if (isrestricted)
		strcat(string, "\n{FF6666}Group Access restricted");
	else
		strcat(string, "\n{66FF66}Group Access unrestricted");

	if (ServerLocked)
		strcat(string, "\n{FF6666}Server Locked");
	else
		strcat(string, "\n{66FF66}Server Unlocked");

	if (AntiSpam)
		strcat(string, "\n{66FF66}Anti-Spam");
	else
		strcat(string, "\n{FF6666}No Anti-Spam");

	if (AutoBal)
		strcat(string, "\n{66FF66}Auto-Balance");
	else
		strcat(string, "\n{FF6666}No Auto-Balance");

	if (AutoPause)
		strcat(string, "\n{66FF66}Auto-Pause");
	else
		strcat(string, "\n{FF6666}No Auto-Pause");

	if (LobbyGuns)
		strcat(string, "\n{66FF66}Guns in Lobby");
	else
		strcat(string, "\n{FF6666}No guns in Lobby");

	if (CPInArena)
		strcat(string, "\n{66FF66}Checkpoint in arena");
	else
		strcat(string, "\n{FF6666}No checkpoint in arena");

	if (AntiMacros)
		strcat(string, "\n{66FF66}Anti-macros system");
	else
		strcat(string, "\n{FF6666}No Anti-macros system");

	if (DeadBodies)
		strcat(string, "\n{66FF66}Dead bodies");
	else
		strcat(string, "\n{FF6666}No dead bodies");

	if (DeathCamera)
		strcat(string, "\n{66FF66}Death camera and its textdraws");
	else
		strcat(string, "\n{FF6666}No death camera and its textdraws");

	if (ShowHPBars)
		strcat(string, "\n{66FF66}HP Bars");
	else
		strcat(string, "\n{FF6666}No HP Bars");

	if (GunmenuRestrictions)
		strcat(string, "\n{66FF66}Gunmenu selection restriction");
	else
		strcat(string, "\n{FF6666}No gunmenu selection restriction");

	if (MeleeAllowed)
		strcat(string, "\n{66FF66}Melee weapon menu");
	else
		strcat(string, "\n{FF6666}No melee weapon menu");

	if (AutoRoundStarter)
		strcat(string, "\n{66FF66}Auto round starter");
	else
		strcat(string, "\n{FF6666}No auto round starter");

	if (RandomDeathMessages)
		strcat(string, "\n{66FF66}Random Death Messages");
	else
		strcat(string, "\n{FF6666}No Random Death Messages");

	if (SightseeingInClassSelection)
		strcat(string, "\n{66FF66}Sightseeing In Class Selection");
	else
		strcat(string, "\n{FF6666}No Sightseeing In Class Selection");

	if (VehicleHealthTextdraw)
		strcat(string, "\n{66FF66}Vehicle Health Information");
	else
		strcat(string, "\n{FF6666}No Vehicle Health Information");

	if (SyncAbuse)
		strcat(string, "\n{66FF66}Sync Abuse system");
	else
		strcat(string, "\n{FF6666}No Sync Abuse system");

	if (ScreenFlashing)
		strcat(string, "\n{66FF66}CP Screen Flashing");
	else
		strcat(string, "\n{FF6666}No CP Screen Flashing");

	if (DefendersWithVehicles)
		strcat(string, "\n{66FF66}Defenders Can Use Vehicles");
	else
		strcat(string, "\n{FF6666}Defenders Can't Use Vehicles");

	Dialog_ShowCallback(playerid1, using inline InlineConfig, DIALOG_STYLE_LIST, COL_PRIM "Config Settings", string, "OK", "Cancel");
	return 1;
}

LoadConfig()
{
	new iString[128];
	new DBResult: res = db_query(sqliteconnection, "SELECT * FROM Configs");
	Skin[NON]		  = 0;

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Attacker Skin
	Skin[ATTACKER] = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Attacker Sub Skin
	Skin[ATTACKER_SUB] = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Defender Skin
	Skin[DEFENDER] = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Defender Sub Skin
	Skin[DEFENDER_SUB] = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Referee Skin
	Skin[REFEREE] = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Server Weather
	MainWeather = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Server Time
	MainTime = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // CP Time
	ConfigCPTime = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Round Time
	ConfigRoundTime = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Total Rounds
	TotalRounds = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Maximum Packetloss
	Max_Packetloss = floatstr(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Maximum Ping
	Max_Ping = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Minimum FPS
	Min_FPS = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Main Spawn
	sscanf(iString, "p<,>ffffd", MainSpawn[0], MainSpawn[1], MainSpawn[2], MainSpawn[3], MainInterior);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Round HP AR
	sscanf(iString, "p<,>dd", RoundAR, RoundHP);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Main Background Colour
	MAIN_BACKGROUND_COLOUR = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", MAIN_TEXT_COLOUR, sizeof(MAIN_TEXT_COLOUR)); // Main Text Colour
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Color Scheme ID
	format(ColScheme, sizeof(ColScheme), "{%s}", iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // CP in arena
	CPInArena = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // AntiMacros
	AntiMacros = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // DeadBodies
	DeadBodies = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // DeathCamera
	DeathCamera = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // ShowHPBars
	ShowHPBars = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // MeleeAllowed
	MeleeAllowed = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", CurrentBaseSet, sizeof(CurrentBaseSet)); // CurrentBaseSet
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // AutoRoundStarter
	AutoRoundStarter = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Game speed
	GAME_SPEED = strval(iString);
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // RandomDeathMessages
	RandomDeathMessages = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // SightseeingInClassSelection
	SightseeingInClassSelection = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // VehicleHealthTextdraw
	VehicleHealthTextdraw = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Defenders With Vehicle
	DefendersWithVehicles = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Sync Abuse
	SyncAbuse = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", iString, sizeof(iString)); // Screen Flash
	ScreenFlashing = strval(iString) == 1;
	db_next_row(res);

	db_get_field_assoc(res, "Value", ServerName, sizeof(ServerName)); // Server Name
	db_next_row(res);

	//db_get_field_assoc(res, "Value", iString, sizeof(iString)); // CurrentArenaSet
	//sscanf(iString, "s[32]", CurrentArenaSet);
	//db_next_row(res);

	db_free_result(res);
	print("Server Config Loaded.");
}
