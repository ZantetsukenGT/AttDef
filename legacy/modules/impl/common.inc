#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_common
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_common
	#endinput
#endif
#define _attdef_impl_common

/*
	Common stuff
*/

forward OnPlayerKicked(playerid);
public OnPlayerKicked(playerid)
{
	Kick(playerid);
	return 1;
}

forward SendTipMessageToAll(bool: calledDuringPause);
public SendTipMessageToAll(bool: calledDuringPause)
{
	if (calledDuringPause)
		TipTimerDuringPause = 0;
	switch (random(16))
	{
		case 0: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Try different gunmenu styles with {FFFFFF}/gunmenustyle");
		case 1: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Want to differentiate your team-mates on radar by color? Use {FFFFFF}/playermarkers");
		case 2: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Use {FFFFFF}/weaponbinds " COL_TIP "to code your own weapon key binds.");
		case 3: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "You can drop a gun by holding it and typing {FFFFFF}/remgun");
		case 4: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "If you're lagging, you can request netcheck with {FFFFFF}/netcheckme");
		case 5: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Disrespect noobs, use {FFFFFF}/deathdiss " COL_TIP "command.");
		case 6: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Getting distracted by some textdraws? Try {FFFFFF}/hud");
		case 7: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Enter no-clip camera mode with /freecam command.");
		case 8: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Play in different duel arenas by means of 'custom' parameter in {FFFFFF}/duel " COL_TIP "command.");
		case 9: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Use {FFFFFF}/cmdhelp [Command name] " COL_TIP "to get info about any command.");
		case 10: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Change your hit sounds with {FFFFFF}/sound " COL_TIP "command.");
		case 11: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Change your time and weather with {FFFFFF}/time " COL_TIP "and {FFFFFF}/weather " COL_TIP "commands.");
		case 12: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Press 'Tab' key and click on a player for quicker operations/commands.");
		case 13: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "You can change your skin with /skin while in lobby, DM or duel.");
		case 14: SendClientMessageToAll(COL_TIP_PRIM_HEX, "Tips: " COL_TIP "Switch round textdraws style with {FFFFFF}/style");
	}
	return 1;
}

SendCommandHelpMessage(playerid, const text[], MessageBoxType: messagebox_type = MSGBOX_TYPE_MIDDLE)
{
	MessageBox(playerid, messagebox_type, "~y~~h~Command Help", text, 5000);
	return 1;
}

SendErrorMessage(playerid, const text[], MessageBoxType: messagebox_type = MSGBOX_TYPE_MIDDLE)
{
	switch (messagebox_type)
	{
		case MSGBOX_TYPE_MIDDLE:
		{
			va_SendClientMessage(playerid, COL_ERROR_HEX, "ERROR: {FFFFFF}%s", text);
		}
		default:
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			MessageBox(playerid, messagebox_type, "~r~~h~Error", text, 5000);
		}
	}
	return 1;
}

SendWarningMessage(playerid, const text[], MessageBoxType: messagebox_type = MSGBOX_TYPE_MIDDLE)
{
	switch (messagebox_type)
	{
		case MSGBOX_TYPE_MIDDLE:
		{
			va_SendClientMessage(playerid, COL_WARNING_HEX, "WARNING: {FFFFFF}%s", text);
		}
		default:
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			MessageBox(playerid, messagebox_type, "~y~~h~Warning", text, 5000);
		}
	}
	return 1;
}

SendUsageMessage(playerid, const text[], MessageBoxType: messagebox_type = MSGBOX_TYPE_MIDDLE)
{
	switch (messagebox_type)
	{
		case MSGBOX_TYPE_MIDDLE:
		{
			va_SendClientMessage(playerid, COL_USAGE_HEX, "USAGE: {FFFFFF}%s", text);
		}
		default:
		{
			PlayerPlaySound(playerid, 5202, 0.0, 0.0, 0.0);
			MessageBox(playerid, messagebox_type, "~b~~h~Correct Syntax", text, 5000);
		}
	}
	return 1;
}

GetColor(color)
{
	new string[9];
	format(string, sizeof(string), "{%06x}", ShiftRGBAToRGB(color));
	return string;
}

GetPlayerCorrectMarkerCol(playerid, forplayerid)
{
	if (!Player[forplayerid][PlayerMarkers])
		return GetPlayerColor(playerid);
	if (TeamHasLeader[Player[playerid][Team]] && TeamLeader[Player[playerid][Team]] == playerid)
		return Player[playerid][Team] == ATTACKER ? ATTACKER_TEAM_LEADER : DEFENDER_TEAM_LEADER;
	if (Player[playerid][AskingForHelp])
		return Player[playerid][Team] == ATTACKER ? ATTACKER_ASKING_HELP : DEFENDER_ASKING_HELP;
	return PlayerColors[playerid];
}

// Checks all players and set idle players to afk mode
AutoAFKCheck()
{
	foreach (new i : Player)
	{
		if (Player[i][PauseCount] > 60 && !Player[i][IsAFK]) // If they've been away for more than 60 seconds
		{
			if (Player[i][Playing])
				RemovePlayerFromRound(i);
			else if (Player[i][ToAddInRound])
				Player[i][ToAddInRound] = false;
			else if (Player[i][Spectating])
				StopSpectate(i);
			else if (Player[i][InDM])
				QuitDM(i);

			Player[i][Team] = NON;
			SetPlayerColor(i, 0xAAAAAAAA);
			TogglePlayerControllable(i, 0);
			Player[i][IsAFK] = true;

			va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has been set to AFK mode automatically due to one minute(+) of inactivity!", Player[i][Name]);
		}
	}
}

CreateDeadBody(playerid, killerid, reason, Float: distance = 0.0, Float: x = 0.0, Float: y = 0.0, Float: z = 0.0)
{
	if (!DeadBodies)
		return;

	if (x == 0.0 && y == 0.0 && z == 0.0)
		GetPlayerPos(playerid, x, y, z);
	if (distance == 0.0 && killerid != INVALID_PLAYER_ID)
		distance = GetPlayerDistanceFromPoint(killerid, x, y, z);

	new Float: angle;
	GetPlayerFacingAngle(playerid, angle);
	new actorid = CreateActor(GetPlayerSkin(playerid), x, y, z, angle);
	SetActorInvulnerable(actorid, 0);
	SetActorHealth(actorid, 0.0);
	new worldid = GetPlayerVirtualWorld(playerid);
	SetActorVirtualWorld(actorid, worldid);
	Iter_Add(DeadBodyActors, actorid);
	new color = 0xFFFFFFFF;
	switch (Player[playerid][Team])
	{
		case ATTACKER: color = 0xF58E8EFF;
		case DEFENDER: color = 0x8E9CF5FF;
	}

	new str[144];
	switch (killerid)
	{
		case INVALID_PLAYER_ID:
		{
			format(str, sizeof str, "Dead body of: %s\nReason: %s", Player[playerid][Name], ReturnWeaponName(reason));
			new Text3D: textlabel = Create3DTextLabel(str, color, x, y, z - 0.3, 20.0, worldid, true);
			Iter_Add(DeadBodyLabels, _: textlabel);
		}
		default:
		{
			format(str, sizeof str, "Dead body of: %s\nMurderer: %s\nDistance: %.1f\nReason: %s", Player[playerid][Name], Player[killerid][Name], distance, ReturnWeaponName(reason));
			new Text3D: textlabel = Create3DTextLabel(str, color, x, y, z - 0.3, 20.0, worldid, true);
			Iter_Add(DeadBodyLabels, _: textlabel);
		}
	}
}

DeleteAllDeadBodies()
{
	if (!DeadBodies)
		return;

	if (Iter_Count(DeadBodyLabels) != 0)
	{
		foreach (new i : DeadBodyLabels)
			Delete3DTextLabel(Text3D: i);

		Iter_Clear(DeadBodyLabels);
	}
	if (Iter_Count(DeadBodyActors) != 0)
	{
		foreach (new i : DeadBodyActors)
			DestroyActor(i);

		Iter_Clear(DeadBodyActors);
	}
}

CheckPlayerNet(playerid)
{
	new pFPS = GetPlayerFPS(playerid);
	new Float: pPL = NetStats_PacketLossPercent(playerid);
	new pPing = GetPlayerPing(playerid);
	if (pFPS < Min_FPS && Player[playerid][PauseCount] < 5 && Player[playerid][FPSCheck])
	{
		Player[playerid][FPSKick]++;
		va_SendClientMessage(playerid, -1, "{FF756D}Low FPS! Warning %d/" #MAX_LOWFPS_WARNINGS " - use /netcheckme", Player[playerid][FPSKick]);

		if (Player[playerid][FPSKick] == MAX_LOWFPS_WARNINGS)
		{
			va_SendClientMessageToAll(
				-1,
				"{FFFFFF}%s " COL_PRIM "has been kicked from the server .: {FFFFFF}Low FPS | %d/%d " COL_PRIM ":.", Player[playerid][Name], pFPS, Min_FPS);
			SetTimerEx("OnPlayerKicked", pPing + 10, false, "i", playerid);
		}
	}
	else
	{
		Player[playerid][FPSKick] = 0;
	}

	if (pPL >= Max_Packetloss && !Player[playerid][FakePacketRenovation] && Player[playerid][PLCheck])
	{
		Player[playerid][PacketKick]++;
		va_SendClientMessage(playerid, -1, "{FF756D}High PL! Warning %d/" #MAX_PACKETLOSS_WARNINGS " - use /netcheckme", Player[playerid][PacketKick]);

		if (Player[playerid][PacketKick] == MAX_PACKETLOSS_WARNINGS)
		{
			va_SendClientMessageToAll(
				-1, "{FFFFFF}%s " COL_PRIM "has been kicked from the server .: {FFFFFF}High Packetloss | %.2f/%.2f " COL_PRIM ":.", Player[playerid][Name],
						pPL, Max_Packetloss);
			SetTimerEx("OnPlayerKicked", pPing + 10, false, "i", playerid);
		}
	}
	else
	{
		Player[playerid][PacketKick] = 0;
	}

	if (pPing >= Max_Ping && Player[playerid][PingCheck])
	{
		Player[playerid][PingKick]++;
		va_SendClientMessage(playerid, -1, "{FF756D}High Ping! Warning %d/" #MAX_HIGHPING_WARNINGS " - use /netcheckme", Player[playerid][PingKick]);

		if (Player[playerid][PingKick] == MAX_HIGHPING_WARNINGS)
		{
			va_SendClientMessageToAll(
				-1, "{FFFFFF}%s " COL_PRIM "has been kicked from the server .: {FFFFFF}High Ping | %d/%d " COL_PRIM ":.", Player[playerid][Name], pPing,
						Max_Ping);
			SetTimerEx("OnPlayerKicked", pPing + 10, false, "i", playerid);
		}
	}
	else
	{
		Player[playerid][PingKick] = 0;
	}
}

bool: IsValidWeapon(weaponid) { return weaponid > 1 && weaponid < 19 || weaponid > 21 && weaponid < 47 && weaponid != 40; }

bool: IsValidSkin(skinid) { return skinid > 74 && skinid < 265 || skinid >= 0 && skinid < 74 || skinid > 272 && skinid < 300; }

stock GetPlayerSpeed(playerid)
{
	new Float: velocity[4];
	GetPlayerVelocity(playerid, velocity[0], velocity[1], velocity[2]);
	velocity[3] = floatsqroot(floatpower(floatabs(velocity[0]), 2.0) + floatpower(floatabs(velocity[1]), 2.0) + floatpower(floatabs(velocity[2]), 2.0)) * 179.28625;
	return floatround(velocity[3]);
}

ShowPlayerClassSelection(playerid)
{
	new str[320], ct[5];

	foreach (new i : Player)
	{
		if (i == playerid)
			continue;

		switch (Player[i][Team])
		{
			case ATTACKER: ct[0]++;
			case DEFENDER: ct[1]++;
			case REFEREE: ct[2]++;
			case ATTACKER_SUB: ct[3]++;
			case DEFENDER_SUB: ct[4]++;
		}
	}
	format(
		str, sizeof(str),
		"Team\tAccessibility\tMembers Count\n{FFFFFF}Auto-assign\tN/A\tN/A\n%s%s{FFFFFF}\t%s\t%d\n%s%s{FFFFFF}\t%s\t%d\n%s%s{FFFFFF}\t%s\t%d\n%s%s{FFFFFF}\t%s\t%d\n%s%s{FFFFFF}\t%s\t%d",
		TextColor[ATTACKER], TeamName[ATTACKER], strlen(GroupAccessPassword[ATTACKER - 1]) > 0 ? "{FF6666}Locked (password required)" : "{66FF66}Open", ct[0], TextColor[DEFENDER],
		TeamName[DEFENDER], strlen(GroupAccessPassword[DEFENDER - 1]) > 0 ? "{FF6666}Locked (password required)" : "{66FF66}Open", ct[1], TextColor[REFEREE], TeamName[REFEREE],
		strlen(GroupAccessPassword[REFEREE - 1]) > 0 ? "{FF6666}Locked (password required)" : "{66FF66}Open", ct[2], TextColor[ATTACKER_SUB], TeamName[ATTACKER_SUB],
		strlen(GroupAccessPassword[ATTACKER_SUB - 1]) > 0 ? "{FF6666}Locked (password required)" : "{66FF66}Open", ct[3], TextColor[DEFENDER_SUB], TeamName[DEFENDER_SUB],
		strlen(GroupAccessPassword[DEFENDER_SUB - 1]) > 0 ? "{FF6666}Locked (password required)" : "{66FF66}Open", ct[4]);

	ShowPlayerDialog(playerid, DIALOG_TEAM_SELECTION, DIALOG_STYLE_TABLIST_HEADERS, "Team Selection", str, "Spawn", "");
}

forward SpawnConnectedPlayer(playerid, team);
public SpawnConnectedPlayer(playerid, team)
{
	switch (team)
	{
		case 0: // auto-assign
		{
			if (!WarMode)
				Player[playerid][Team] = GetTeamWithLessPlayers();
			else if (strfind(Player[playerid][Name], TeamName[ATTACKER], true) != -1)
				Player[playerid][Team] = ATTACKER;
			else if (strfind(Player[playerid][Name], TeamName[DEFENDER], true) != -1)
				Player[playerid][Team] = DEFENDER;
			else
				Player[playerid][Team] = GetTeamWithLessPlayers();
		}
		case 1: Player[playerid][Team] = ATTACKER;
		case 2: Player[playerid][Team] = DEFENDER;
		case 3: Player[playerid][Team] = REFEREE;
		case 4: Player[playerid][Team] = ATTACKER_SUB;
		case 5: Player[playerid][Team] = DEFENDER_SUB;
	}

	SwitchTeamFix(playerid, false, false, false);
	SetPlayerWeather(playerid, Player[playerid][Weather]);
	SetPlayerTime(playerid, Player[playerid][Time], 0);

	PlayerTextDrawShow(playerid, BaseID_VS[playerid]);

	if (PlayerInterface[playerid][INTERFACE_NET])
		PlayerTextDrawShow(playerid, FPSPingPacket[playerid]);
	else
		PlayerTextDrawHide(playerid, FPSPingPacket[playerid]);

	PlayerTextDrawShow(playerid, RoundKillDmgTDmg[playerid]);

	if (Current != -1)
		ShowRoundStats(playerid);

	if (PlayerInterface[playerid][INTERFACE_SPEC])
		PlayerTextDrawShow(playerid, WhoSpec[playerid]);
	else
		PlayerTextDrawHide(playerid, WhoSpec[playerid]);

	TextDrawShowForPlayer(playerid, TeamHpLose[0]);
	TextDrawShowForPlayer(playerid, TeamHpLose[1]);
	TextDrawShowForPlayer(playerid, AttHpLose);
	TextDrawShowForPlayer(playerid, DefHpLose);

	PlayerTextDrawShow(playerid, TD_RoundSpec[playerid]);
	PlayerTextDrawShow(playerid, BaseID_VS[playerid]);

	if (WarMode)
		ShowMatchScoreBoard(playerid);

	Player[playerid][Spawned] = true;
	SpawnInLobby(playerid);

	HideAllTeamBarsForPlayer(playerid);

	LoadPlayerVariables(playerid);
	return 1;
}

SpawnInLobby(playerid)
{
	SetSpawnInfo(playerid, playerid, Skin[Player[playerid][Team]], MainSpawn[0] + RandomMinMax(-3, 3), MainSpawn[1] + RandomMinMax(-3, 3), MainSpawn[2] + 2, MainSpawn[3], 0, 0, 0, 0, 0, 0);
	if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		TogglePlayerSpectating(playerid, false);
	else
		SpawnPlayer(playerid);
}

ShowPlayerDeathMessage(killerid, playerid)
{
	if (!Player[killerid][HasDeathQuote] || !DeathCamera)
		return;
	MessageBox(
		playerid, MSGBOX_TYPE_MIDDLE, va_return("%s~h~%s ~w~is dissing you", TDC[Player[killerid][Team]], Player[killerid][Name]), va_return("%s", DeathMessageStr[killerid]),
		DEATH_CAMERA_DURATION);
}

RecountPlayersOnCP()
{
	PlayersInCP = 0;

	if (GameType == BASE || GameType == ARENA && CPInArena)
	{
		foreach (new i : PlayersInRound)
		{
			Player[i][WasInCP] = false;
			if (IsPlayerInCheckpoint(i))
				CallLocalFunction("OnPlayerEnterCheckpoint", "i", i);
		}
	}

	if (PlayersInCP != 0)
		return PlayersInCP;

	TeamCapturingCP = NON;
	CurrentCPTime	= ConfigCPTime + 1;
	TextDrawHideForAll(EN_CheckPoint);
	TextDrawHideForAll(CheckpointWarningBox);
	TextDrawColor(timerCircleTD, 0x00000033);
	GangZoneStopFlashForAll(CPZone);
	foreach (new i : Player)
	{
		if (!Player[i][Spawned])
			continue;

		if (Player[i][RoundTDStyle] != 1)
			continue;

		TextDrawShowForPlayer(i, timerCircleTD);
	}
	return PlayersInCP;
}

RemoveVendingMachinesForPlayer(playerid)
{
	RemoveBuildingForPlayer(playerid, 955, 0.0, 0.0, 0.0, 20000.0);	 // CJ_EXT_SPRUNK
	RemoveBuildingForPlayer(playerid, 956, 0.0, 0.0, 0.0, 20000.0);	 // CJ_EXT_CANDY
	RemoveBuildingForPlayer(playerid, 1209, 0.0, 0.0, 0.0, 20000.0); // vendmach
	RemoveBuildingForPlayer(playerid, 1302, 0.0, 0.0, 0.0, 20000.0); // vendmachfd
	RemoveBuildingForPlayer(playerid, 1775, 0.0, 0.0, 0.0, 20000.0); // CJ_SPRUNK1
	RemoveBuildingForPlayer(playerid, 1776, 0.0, 0.0, 0.0, 20000.0); // CJ_CANDYVENDOR
	RemoveBuildingForPlayer(playerid, 1977, 0.0, 0.0, 0.0, 20000.0); // vendin3
}

RemoveUselessObjectsForPlayer(playerid)
{
	RemoveVendingMachinesForPlayer(playerid);
	RemoveBuildingForPlayer(playerid, 1220, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1221, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1230, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1299, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1421, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1448, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1449, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1450, 0.0, 0.0, 0.0, 6000.0); // boxes that make you lose hp
	RemoveBuildingForPlayer(playerid, 1440, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1421, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1438, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1338, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1219, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1676, 0.0, 0.0, 0.0, 6000.0); // exploding gas tank
	RemoveBuildingForPlayer(playerid, 1686, 0.0, 0.0, 0.0, 6000.0);
}
/*
randomExFloat(Float:min, Float:max)
{
	new rand = random(floatround(max-min, floatround_round))+floatround(min, floatround_round);
	return rand;
}
*/
/*
Function: LogAdminCommand
cmd[]: the entered command
adminid: the admin who enters the command
playerid: the player who the command hits (use INVALID_PLAYER_ID to ignore this)
*/
LogAdminCommand(const cmd[], adminid, playerid)
{
	new File: log = fopen("admin_command_log.txt", io_append);

	if (log)
	{
		new Year, Month, Day, Hours, Minutes, Seconds;
		getdate(Year, Month, Day);
		gettime(Hours, Minutes, Seconds);
		if (playerid != INVALID_PLAYER_ID)
			fwrite(
				log, va_return(
						 "[%02d/%02d/%d][%02d:%02d:%02d] %s [%d] has used the command (/%s) at %s [%d]. \r\n", Day, Month, Year, Hours, Minutes, Seconds, Player[adminid][Name],
						 adminid, cmd, Player[playerid][Name], playerid));
		else
			fwrite(
				log,
				va_return("[%02d/%02d/%d][%02d:%02d:%02d] %s [%d] has used the command (/%s). \r\n", Day, Month, Year, Hours, Minutes, Seconds, Player[adminid][Name], adminid, cmd));
		fclose(log);
	}
	return 1;
}

ClearAdminCommandLog()
{
	new File: log = fopen("admin_command_log.txt", io_write);
	fwrite(log, "");
	fclose(log);
}

forward HideTargetInfo(playerid);
public HideTargetInfo(playerid)
{
	TargetInfoData[playerid][TargetInfoTimer] = 0;
	PlayerTextDrawHide(playerid, TargetInfoData[playerid][TargetInfoTD]);
	return 1;
}

ShowTargetInfo(playerid, targetid)
{
	if (targetid == INVALID_PLAYER_ID || playerid == INVALID_PLAYER_ID)
		return 1;

	new currentTick = GetTickCount();
	if (targetid == TargetInfoData[playerid][TargetInfoLastTarget] && currentTick - TargetInfoData[playerid][TargetInfoLastTick] < 1000)
		return 1;

	if (TargetInfoData[playerid][TargetInfoTimer])
		KillTimer(TargetInfoData[playerid][TargetInfoTimer]);
	TargetInfoData[playerid][TargetInfoTimer] = SetTimerEx("HideTargetInfo", 5000, false, "i", playerid);

	va_PlayerTextDrawSetString(playerid, TargetInfoData[playerid][TargetInfoTD], "%sName: %s%s~n~%sPing: %s%d   %sFPS: %s%d~n~%sPL: %s%.1f   %sHP: %s%d", MAIN_TEXT_COLOUR, TDC[Player[targetid][Team]], Player[targetid][NameWithoutTag],
		MAIN_TEXT_COLOUR, TDC[Player[targetid][Team]], GetPlayerPing(targetid), MAIN_TEXT_COLOUR, TDC[Player[targetid][Team]], GetPlayerFPS(targetid), MAIN_TEXT_COLOUR,
		TDC[Player[targetid][Team]], NetStats_PacketLossPercent(targetid), MAIN_TEXT_COLOUR, TDC[Player[targetid][Team]], GetHP(targetid) + GetAP(targetid));

	PlayerTextDrawShow(playerid, TargetInfoData[playerid][TargetInfoTD]);
	TargetInfoData[playerid][TargetInfoLastTick]   = currentTick;
	TargetInfoData[playerid][TargetInfoLastTarget] = targetid;
	return 1;
}

forward HideAnnForAll();
public HideAnnForAll()
{
	AnnTimer = 0;
	TextDrawHideForAll(AnnTD);
}

bool: CanPlay(playerid)
{
	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return false;

	if (Player[playerid][InDuel] || Player[playerid][IsAFK] || !Player[playerid][Spawned])
		return false; // can not play

	return true; // can play
}

bool: IsValidSound(soundid)
{
	for (new i = 0; i < sizeof(ValidSounds); ++i)
	{
		if (ValidSounds[i] == soundid)
			return true;
	}
	return false;
}

GetWeaponID(const weaponname[])
{
	for (new i = 0; i < sizeof(g_WeaponName); ++i)
	{
		if (strfind(g_WeaponName[i], weaponname, true) != -1)
			return i;
	}
	return -1;
}

GetWeaponModelFromID(weaponid)
{
	new model = -1;
	switch (weaponid)
	{
		case 1: model = 331;
		case 2: model = 333;
		case 3: model = 334;
		case 4: model = 335;
		case 5: model = 336;
		case 6: model = 337;
		case 7: model = 338;
		case 8: model = 339;
		case 9: model = 341;
		case 10: model = 321;
		case 11: model = 322;
		case 12: model = 323;
		case 13: model = 324;
		case 14: model = 325;
		case 15: model = 326;
		case 16: model = 342;
		case 17: model = 343;
		case 18: model = 344;
		case 22: model = 346;
		case 23: model = 347;
		case 24: model = 348;
		case 25: model = 349;
		case 26: model = 350;
		case 27: model = 351;
		case 28: model = 352;
		case 29: model = 353;
		case 30: model = 355;
		case 31: model = 356;
		case 32: model = 372;
		case 33: model = 357;
		case 34: model = 358;
		case 35: model = 359;
		case 36: model = 360;
		case 37: model = 361;
		case 38: model = 362;
		case 39: model = 363;
		case 41: model = 365;
		case 42: model = 366;
		case 46: model = 371;
	}
	return model;
}

OnPlayerAmmoUpdate(playerid)
{
	if (Player[playerid][Playing])
	{
		new weapons;
		new Ammo, TotalShots, Float: accuracy;

		for (new k = 2; k < 8; ++k)
		{
			GetPlayerWeaponData(playerid, k, weapons, Ammo);
			if (Ammo > 10)
				TotalShots += (9999 - Ammo);
		}

		accuracy = TotalShots == 0 ? 0.0 : floatmul(100.0, floatdiv(Player[playerid][shotsHit], TotalShots));

		Player[playerid][TotalBulletsFired] += TotalShots;
		Player[playerid][TotalshotsHit] += Player[playerid][shotsHit];
		Player[playerid][Accuracy] = accuracy;
		Player[playerid][TotalAccuracy] += accuracy;
	}
}

bool: DoesPlayerHaveWeaponInSlot(playerid, slot)
{
	new wep, ammo;
	GetPlayerWeaponData(playerid, slot, wep, ammo);
	return ammo > 0;
}

bool: DoesPlayerHaveWeapon(playerid, weaponid)
{
	new wep, ammo;
	GetPlayerWeaponData(playerid, GetWeaponSlot(weaponid), wep, ammo);
	return wep == weaponid && ammo > 0;
}

#if defined _YSF_included
RemovePlayerWeapon(playerid, weaponid)
{
	if(!DoesPlayerHaveWeapon(playerid, weaponid))
		return 0;

	new plyWeapons[12];
	new plyAmmo[12], armedID;

	new wep, ammo;
	for(new slot = 0; slot != 12; slot++)
	{
		GetPlayerWeaponData(playerid, slot, wep, ammo);

		if(wep != weaponid)
		{
			GetPlayerWeaponData(playerid, slot, plyWeapons[slot], plyAmmo[slot]);
		}
	}

	armedID = GetPlayerWeapon(playerid);

	ResetPlayerWeapons(playerid);
	for(new slot = 0; slot != 12; slot++)
	{
		GivePlayerWeapon(playerid, plyWeapons[slot], plyAmmo[slot]);
	}

	if( armedID != weaponid ) SetPlayerArmedWeapon(playerid,armedID); //give last armedweapon
	else SetPlayerArmedWeapon(playerid,0);//give fist if player armed weapon was knife
	return 1;
}
#endif 

GetCardinalPoint(Float: degree)
{
	// this function return a string that contain the Cardinal point of a heading direction

	// Create string and initialize it to hold the direction text
	new CardinalPoint[11];

	/*
		From SA:MP wiki

		"Angles are reversed in GTA:SA; 90 degrees would be
		East in the real world, but in GTA:SA 90 degrees is
		in fact West. North and South are still 0/360 and 180
	*/
	degree = 360.0 - degree; // correct conversion

	// each cardinal point cover 45degree (45 X 8 = 360)
	if (337.5 <= degree <= 360)
		strcat(CardinalPoint, "North");
	else if (0 <= degree <= 22.5)
		strcat(CardinalPoint, "North");
	else if (22.5 <= degree <= 67.5)
		strcat(CardinalPoint, "North East");
	else if (67.5 <= degree <= 112.5)
		strcat(CardinalPoint, "East");
	else if (112.5 <= degree <= 157.5)
		strcat(CardinalPoint, "South East");
	else if (157.5 <= degree <= 202.5)
		strcat(CardinalPoint, "South");
	else if (202.5 <= degree <= 247.5)
		strcat(CardinalPoint, "South West");
	else if (247.5 <= degree <= 292.5)
		strcat(CardinalPoint, "West");
	else if (292.5 <= degree <= 337.5)
		strcat(CardinalPoint, "North West");
	else
		strcat(CardinalPoint, "Unknown"); // error

	return CardinalPoint; // we return our string
}

SwapTeams()
{
	new MyVehicle = -1;
	new Seat;
	new Iterator: ToFixSwitch<MAX_PLAYERS>;
	foreach (new i : Player)
	{
		if (Player[i][Team] == ATTACKER)
			Player[i][Team] = DEFENDER;
		else if (Player[i][Team] == ATTACKER_SUB)
			Player[i][Team] = DEFENDER_SUB;
		else if (Player[i][Team] == DEFENDER)
			Player[i][Team] = ATTACKER;
		else if (Player[i][Team] == DEFENDER_SUB)
			Player[i][Team] = ATTACKER_SUB;

		MyVehicle = GetPlayerVehicleID(i);
		if (MyVehicle)
			Seat = GetPlayerVehicleSeat(i);

		if (MyVehicle != -1)
			PutPlayerInVehicle(i, MyVehicle, Seat);
		Iter_Add(ToFixSwitch, i);
	}

	for (new i = 0; i < SAVE_SLOTS; ++i)
	{
		if (SaveVariables[i][pName][0])
		{
			if (SaveVariables[i][pTeam] == ATTACKER)
				SaveVariables[i][pTeam] = DEFENDER;
			else if (SaveVariables[i][pTeam] == DEFENDER)
				SaveVariables[i][pTeam] = ATTACKER;
		}
	}

	new TempScore		= TeamScore[ATTACKER];
	TeamScore[ATTACKER] = TeamScore[DEFENDER];
	TeamScore[DEFENDER] = TempScore;

	new TempName[24];
	TempName			   = TeamName[ATTACKER];
	TeamName[ATTACKER]	   = TeamName[DEFENDER];
	TeamName[DEFENDER]	   = TempName;
	TempName			   = TeamName[ATTACKER_SUB];
	TeamName[ATTACKER_SUB] = TeamName[DEFENDER_SUB];
	TeamName[DEFENDER_SUB] = TempName;

	UpdateTeamScoreTextDraw();
	UpdateTeamNameTextDraw();

	// Fix player teams after switching
	foreach (new i : ToFixSwitch)
	{
		SwitchTeamFix(i, false, false);
	}
	Iter_Clear(ToFixSwitch);

	va_SendClientMessageToAll(-1, "{FFFFFF}Teams are swapped - {FF0033}Attackers: {FFFFFF}%s | {3344FF}Defenders: {FFFFFF}%s", TeamName[ATTACKER], TeamName[DEFENDER]);
	FixVsTextDraw();
	return 1;
}

forward DoAutoBalance();
public DoAutoBalance()
{
	BalanceTeams();
	if (!PreMatchResultsShowing)
		AllowStartBase = true;
	SendClientMessageToAll(COL_PRIM_HEX, "Teams have been auto-balanced.");
}

forward DontAutoBalance();
public DontAutoBalance()
{
	if (!PreMatchResultsShowing)
		AllowStartBase = true;
}

BalanceTeams()
{
	new TotalAttackers;
	new TotalDefenders;

	foreach (new i : Player)
	{
		if (Player[i][Spawned] && !Player[i][InDuel] && (Player[i][Team] == ATTACKER || Player[i][Team] == DEFENDER))
		{
			new tid = random(2);
			if (tid == 0)
			{
				Player[i][Team] = DEFENDER;
				TotalDefenders++;
			}
			else if (tid == 1)
			{
				Player[i][Team] = ATTACKER;
				TotalAttackers++;
			}
			SwitchTeamFix(i, false, false);
		}
	}

	new Divisor = floatround((TotalDefenders + TotalAttackers) / 2);

	foreach (new i : Player)
	{
		if (!Player[i][InDuel] && (Player[i][Team] == ATTACKER || Player[i][Team] == DEFENDER))
		{
			new randomnum = random(2);
			switch (randomnum)
			{
				case 0:
				{
					if (TotalDefenders <= Divisor)
					{
						if (Player[i][Team] == ATTACKER)
							TotalAttackers--;
						Player[i][Team] = DEFENDER;
						TotalDefenders++;
						SwitchTeamFix(i, false, false);
					}
					else if (TotalAttackers <= Divisor)
					{
						if (Player[i][Team] == DEFENDER)
							TotalDefenders--;
						Player[i][Team] = ATTACKER;
						TotalAttackers++;
						SwitchTeamFix(i, false, false);
					}
				}
				case 1:
				{
					if (TotalAttackers <= Divisor)
					{
						if (Player[i][Team] == DEFENDER)
							TotalDefenders--;
						Player[i][Team] = ATTACKER;
						TotalAttackers++;
						SwitchTeamFix(i, false, false);
					}
					else if (TotalDefenders <= Divisor)
					{
						if (Player[i][Team] == ATTACKER)
							TotalAttackers--;
						Player[i][Team] = DEFENDER;
						TotalDefenders++;
						SwitchTeamFix(i, false, false);
					}
				}
			}
			if (TotalDefenders == TotalAttackers)
				break;
		}
	}
	FixVsTextDraw();
	return 1;
}

SwitchTeamFix(playerid, bool: message = true, bool: fixvs = true, bool: changeskin = true)
{
	if (message)
	{
		va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has switched to: {FFFFFF}%s", Player[playerid][Name], TeamName[Player[playerid][Team]]);
	}

	UpdateRoundKillDmgTDmg(playerid);

	ColorFix(playerid);
	if (fixvs && Current == -1)
		FixVsTextDraw();

	if (changeskin)
		SetPlayerSkin(playerid, Skin[Player[playerid][Team]]);

	SetCameraBehindPlayer(playerid);
	HideAllTeamBarsForPlayer(playerid);
}

GetTeamWithLessPlayers()
{
	new attacker, defender;
	switch (Current)
	{
		case -1:
		{
			foreach (new i : Player)
			{
				switch (Player[i][Team])
				{
					case DEFENDER: defender++;
					case ATTACKER: attacker++;
				}
			}
		}
		default:
		{
			foreach (new i : PlayersInRound)
			{
				switch (Player[i][Team])
				{
					case DEFENDER: defender++;
					case ATTACKER: attacker++;
				}
			}
		}
	}
	return defender <= attacker ? DEFENDER : ATTACKER;
}

EnableMatchInterface(playerid)
{
	SelectTextDraw(playerid, 0xFF0000FF);
	PlayerOnInterface { playerid } = true;
	TextDrawShowForPlayer(playerid, WarModeText);
	TextDrawShowForPlayer(playerid, SettingBox);
	TextDrawShowForPlayer(playerid, LockServerTD);
	return TextDrawShowForPlayer(playerid, CloseText);
}

DisableMatchInterface(playerid)
{
	CancelSelectTextDraw(playerid);
	TextDrawHideForPlayer(playerid, WarModeText);
	TextDrawHideForPlayer(playerid, SettingBox);
	TextDrawHideForPlayer(playerid, LockServerTD);
	TextDrawHideForPlayer(playerid, CloseText);
	PlayerOnInterface { playerid } = false;
}

bool: IsPlayerInArea(playerid, Float: minx, Float: maxx, Float: miny, Float: maxy)
{
	new Float: x,
		Float: y,
		Float: z;
	GetPlayerPos(playerid, x, y, z);
	return x > minx && x < maxx && y > miny && y < maxy;
}

/*
GetPlayerHighestScores(array[][rankingEnum], left, right)
{
    new
        tempLeft = left,
        tempRight = right,
        pivot = array[(left + right) / 2][player_Score],
        tempVar
    ;
    while(tempLeft <= tempRight)
    {
        while(array[tempLeft][player_Score] > pivot) tempLeft++;
        while(array[tempRight][player_Score] < pivot) tempRight--;

        if(tempLeft <= tempRight)
        {
            tempVar = array[tempLeft][player_Score], array[tempLeft][player_Score] = array[tempRight][player_Score], array[tempRight][player_Score] = tempVar;
            tempVar = array[tempLeft][player_ID], array[tempLeft][player_ID] = array[tempRight][player_ID], array[tempRight][player_ID] = tempVar;
//			format(tempVarStr, sizeof(tempVarStr), array[tempLeft][player_Name]); format(array[tempLeft][player_Name], MAX_PLAYER_NAME, array[tempRight][player_Name]); format(array[tempRight][player_Name], MAX_PLAYER_NAME, tempVarStr);
            //tempVarStr = array[tempLeft][player_Name], array[tempLeft][player_Name] = array[tempRight][player_Name], array[tempRight][player_Name] = tempVarStr;
            tempVar = array[tempLeft][player_Kills], array[tempLeft][player_Kills] = array[tempRight][player_Kills], array[tempRight][player_Kills] = tempVar;
            tempVar = array[tempLeft][player_Deaths], array[tempLeft][player_Deaths] = array[tempRight][player_Deaths], array[tempRight][player_Deaths] = tempVar;
            tempVar = array[tempLeft][player_Team], array[tempLeft][player_Team] = array[tempRight][player_Team], array[tempRight][player_Team] = tempVar;
            tempLeft++, tempRight--;
        }
    }
    if(left < tempRight) GetPlayerHighestScores(array, left, tempRight);
    if(tempLeft < right) GetPlayerHighestScores(array, tempLeft, right);
}*/

GetPlayerHighestScores2(array[][rankingEnum], names[][MAX_PLAYER_NAME], left, right)
{
	new tempLeft = left, tempRight = right, pivot = array[(left + right) / 2][player_Score], tempVar, tempVarStr[MAX_PLAYER_NAME];
	while (tempLeft <= tempRight)
	{
		while (array[tempLeft][player_Score] > pivot) tempLeft++;
		while (array[tempRight][player_Score] < pivot) tempRight--;

		if (tempLeft <= tempRight)
		{
			tempVar = array[tempLeft][player_Score], array[tempLeft][player_Score] = array[tempRight][player_Score], array[tempRight][player_Score] = tempVar;
			tempVar = array[tempLeft][player_ID], array[tempLeft][player_ID] = array[tempRight][player_ID], array[tempRight][player_ID] = tempVar;
			tempVarStr = names[tempLeft], names[tempLeft] = names[tempRight], names[tempRight] = tempVarStr;
			tempVar = array[tempLeft][player_Kills], array[tempLeft][player_Kills] = array[tempRight][player_Kills], array[tempRight][player_Kills] = tempVar;
			tempVar = array[tempLeft][player_Deaths], array[tempLeft][player_Deaths] = array[tempRight][player_Deaths], array[tempRight][player_Deaths] = tempVar;
			tempVar = array[tempLeft][player_Team], array[tempLeft][player_Team] = array[tempRight][player_Team], array[tempRight][player_Team] = tempVar;
			tempVar = array[tempLeft][player_TPlayed], array[tempLeft][player_TPlayed] = array[tempRight][player_TPlayed], array[tempRight][player_TPlayed] = tempVar;
			tempVar = array[tempLeft][player_HP], array[tempLeft][player_HP] = array[tempRight][player_HP], array[tempRight][player_HP] = tempVar;
			tempVar = array[tempLeft][player_Acc], array[tempLeft][player_Acc] = array[tempRight][player_Acc], array[tempRight][player_Acc] = tempVar;
			tempVar = array[tempLeft][player_Overall], array[tempLeft][player_Overall] = array[tempRight][player_Overall], array[tempRight][player_Overall] = tempVar;
			tempLeft++, tempRight--;
		}
	}
	if (left < tempRight)
		GetPlayerHighestScores2(array, names, left, tempRight);
	if (tempLeft < right)
		GetPlayerHighestScores2(array, names, tempLeft, right);
}

forward SetCPForPlayer(playerid);
public SetCPForPlayer(playerid)
{
	switch (GameType)
	{
		case BASE:
		{
			SetPlayerCheckpoint(playerid, BCPSpawn[Current][0], BCPSpawn[Current][1], BCPSpawn[Current][2], 2);
			GangZoneShowForPlayer(playerid, CPZone, GANGZONE_CP);
		}
		case ARENA:
		{
			if (!CPInArena)
				return 0;
			SetPlayerCheckpoint(playerid, ACPSpawn[Current][0], ACPSpawn[Current][1], ACPSpawn[Current][2], 2);
			GangZoneShowForPlayer(playerid, CPZone, GANGZONE_CPARENA);
		}
	}
	return 1;
}

forward RespawnInVehicleAfterComeBack(playerid, vehicleid, seatid);
public RespawnInVehicleAfterComeBack(playerid, vehicleid, seatid)
{
	new ct = 0;
	foreach (new k : Player)
	{
		if (GetPlayerVehicleID(k) == vehicleid && GetPlayerVehicleSeat(k) == seatid)
			ct++;
	}
	if (ct == 0)
		PutPlayerInVehicle(playerid, vehicleid, seatid);
	return 1;
}

bool: IsTeamTheSame(team1, team2)
{
	if (team1 == team2)
		return true;
	else if (team1 == DEFENDER && team2 == DEFENDER_SUB || team1 == DEFENDER_SUB && team2 == DEFENDER)
		return true;
	else if (team1 == ATTACKER && team2 == ATTACKER_SUB || team1 == ATTACKER_SUB && team2 == ATTACKER)
		return true;

	return false;
}

ResetPlayerWorldBounds(playerid) { SetPlayerWorldBounds(playerid, 20000.0000, -20000.0000, 20000.0000, -20000.0000); }

ColorFix(playerid)
{
	if (Player[playerid][Playing])
	{
		switch (Player[playerid][Team])
		{
			case ATTACKER: SetPlayerColor(playerid, ATTACKER_PLAYING);
			case DEFENDER: SetPlayerColor(playerid, DEFENDER_PLAYING);
			case REFEREE: SetPlayerColor(playerid, REFEREE_COLOR);
		}

		new team = Player[playerid][Team];
		if (TeamHasLeader[team] && TeamLeader[team] == playerid)
			PlayerLeadTeam(playerid, true, false);
		return;
	}

	switch (Player[playerid][Team])
	{
		case ATTACKER: SetPlayerColor(playerid, ATTACKER_NOT_PLAYING);
		case DEFENDER: SetPlayerColor(playerid, DEFENDER_NOT_PLAYING);
		case REFEREE: SetPlayerColor(playerid, REFEREE_COLOR);
		case ATTACKER_SUB: SetPlayerColor(playerid, ATTACKER_SUB_COLOR);
		case DEFENDER_SUB: SetPlayerColor(playerid, DEFENDER_SUB_COLOR);
	}
}

RadarFix(playerid = INVALID_PLAYER_ID)
{
	if (playerid == INVALID_PLAYER_ID) // if markers need a global update
	{
		foreach (new i : Player)
		{
			foreach (new x : Player)
			{
				CallLocalFunction("OnPlayerStreamIn", "ii", i, x);
			}
		}
		return;
	}

	// if only one player's color is changed and needs updating
	foreach (new i : Player)
	{
		CallLocalFunction("OnPlayerStreamIn", "ii", playerid, i);
	}
}

ClearChat()
{
	for (new i = 0; i < 10; i++) SendClientMessageToAll(-1, " ");
}

GetVehicleModelID(const vehiclename[])
{
	for (new i = 0; i < 211; i++)
	{
		if (strfind(aVehicleNames[i], vehiclename, true) != -1)
			return i + 400;
	}
	return -1;
}

bool: IsAirVehicle(vehicleid)
{
	if (vehicleid == 0 || vehicleid == INVALID_VEHICLE_ID)
		return false;

	switch (GetVehicleModel(vehicleid))
	{
		case 417, 425, 447, 460, 469, 476, 487, 488, 497, 511, 512, 513, 519, 520, 548, 553, 563, 577, 592, 593:
		{
			return true;
		}
	}
	return false;
}

ClearKillList()
{
	for (new i = 0; i < 5; i++) { SendDeathMessage(255, 50, 255); }
}

DestroyUnusedVehicles() { FreezeV_DestroyAll(); }

forward ForceRespectate(playerid);
public ForceRespectate(playerid)
{
	foreach (new i : PlayerSpectators[playerid])
		SpectatePlayer(i, playerid);
}

SyncPlayer(playerid)
{
	// Restrictions
	new currentTick = GetTickCount();
	if (currentTick - Player[playerid][LastTimeSynced] < 1000)
		return 1;
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		return 1;
	if (GBUG_IsPerformingEntering(playerid))
		return 1;
	if ((RoundPaused || !AllowSync) && Player[playerid][Playing])
		return 1;
	if (Player[playerid][OnGunmenu])
		return SendErrorMessage(playerid, "Can't sync while in gunmenu");
	if (Player[playerid][IsAFK] || !IsPlayerControllable(playerid))
		return SendErrorMessage(playerid, "Can't sync while frozen or in AFK mode");

	Player[playerid][LastTimeSynced] = currentTick;
	// Set spectators to re-spectate
	if (Player[playerid][BeingSpeced])
		SetTimerEx("ForceRespectate", GetPlayerPing(playerid) + 10, false, "i", playerid);

	ResyncPlayer(playerid);
	return 1;
}

FixVsTextDraw(exception = -1)
{
	if (Current == -1)
	{
		new str[32];
		new ct[2];
		foreach (new i : Player)
		{
			if (i == exception)
				continue;

			switch (Player[i][Team])
			{
				case ATTACKER: ct[0]++;
				case DEFENDER: ct[1]++;
			}
		}
		format(str, sizeof(str), "~r~%d  %svs  ~b~~h~%d", ct[0], MAIN_TEXT_COLOUR, ct[1]);
		foreach (new i : Player)
			PlayerTextDrawSetString(i, BaseID_VS[i], str);
	}
	return 1;
}

Float: GetDistanceBetweenPlayers(playerid, toplayerid)
{
	if (playerid == INVALID_PLAYER_ID || toplayerid == INVALID_PLAYER_ID)
		return -1.0;

	new Float: Pos[2][3];
	GetPlayerPos(playerid, Pos[0][0], Pos[0][1], Pos[0][2]);
	GetPlayerPos(toplayerid, Pos[1][0], Pos[1][1], Pos[1][2]);
	return floatsqroot(
		floatpower(floatabs(floatsub(Pos[1][0], Pos[0][0])), 2) + floatpower(floatabs(floatsub(Pos[1][1], Pos[0][1])), 2)
		+ floatpower(floatabs(floatsub(Pos[1][2], Pos[0][2])), 2));
}

SpawnInDM(playerid, DMID)
{
	Player[playerid][InDM] = true;

	ResetPlayerWeapons(playerid); // Reset all player weapons

	if (Player[playerid][DmPosX] == -1.0)
		SetSpawnInfo(
			playerid, playerid, Skin[Player[playerid][Team]], DMSpawn[DMID][0] + RandomMinMax(-1, 1), DMSpawn[DMID][1] + RandomMinMax(-1, 1), DMSpawn[DMID][2], DMSpawn[DMID][3], DMWeapons[DMID][0],
			9999, DMWeapons[DMID][1], 9999, DMWeapons[DMID][2], 9999);
	else
		SetSpawnInfo(
			playerid, playerid, Skin[Player[playerid][Team]], Player[playerid][DmPosX], Player[playerid][DmPosY], DMInterior[DMID] ? Player[playerid][DmPosZ] + 1 : Player[playerid][DmPosZ], Player[playerid][DmAngle],
			DMWeapons[DMID][0], 9999, DMWeapons[DMID][1], 9999, DMWeapons[DMID][2], 9999);

	SetPlayerInterior(playerid, DMInterior[DMID]);
	Player[playerid][IgnoreSpawn] = true; // Make sure you ignore OnPlayerSpawn, else you will just spawn in
										  // lobby (because u are about to use SpawnPlayer).
	SpawnPlayer(playerid);				  // Spawns players, in this case we have SetSpawnInfo (but still
										  // you need to make sure OnPlayerSpawn is ignored);

	SetPlayerVirtualWorld(
		playerid,
		Player[playerid][VWorld]); // Put player in a different virtual world so that if you
								   // create a DM in your lobby and you join the DM, you
								   // won't be able to see other players in the lobby.
	SetHP(playerid, 100);
	SetAP(playerid, 100);
}

QuitDM(playerid)
{
	Player[playerid][DmPosX]  = -1.0;
	Player[playerid][DmPosY]  = -1.0;
	Player[playerid][DmPosZ]  = -1.0;
	Player[playerid][DmAngle] = -1.0;
	if (Player[playerid][Playing])
		return 1;
	if (!Player[playerid][InDM])
		return 1;

	Player[playerid][InDM]	  = false;
	Player[playerid][DMReadd] = 0;
	SpawnInLobby(playerid);
	return 1;
}

bool: IsSafeGametext(const text[])
{
	new cnt = 0;
	for (new i = 0, j = strlen(text); i < j; i++)
	{
		if (text[i] == '~')
			cnt++;
	}
	return bool:IsEven(cnt);
}

// Function written by Slice to help fix vehicle bad modding (tweaked it a little bit)
bool: IsVehicleComponentLegal(vehiclemodel, componentid)
{
	// These is the only case with componentids > 1191 (saves ~1kb in the array)
	if (vehiclemodel == 576 && (componentid == 1192 || componentid == 1193))
		return true;

	new s_LegalMods[][] = { { 54273792, 0, 16776704, 7, 0, 0 },
							{ 35268602, 0, 16776704, 7, 245760, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 37431173, 0, 16776704, 7, 0, 0 },
							{ 45893379, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 62531466, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 42862474, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 36767556, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 36177722, 0, 16776704, 7, 0, 0 },
							{ 45958913, 0, 16776704, 7, 0, 0 },
							{ 37365632, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 36177786, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 41560010, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 42084234, 0, 16776704, 7, 245760, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 37619648, 0, 16776704, 7, 0, 0 },
							{ 57685808, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 52242293, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 46024584, 0, 16776704, 7, 245760, 0 },
							{ 33621873, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 43651022, 0, 16776704, 7, 49152, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 54011648, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 37717909, 0, 16776704, 7, 0, 0 },
							{ 43976588, 0, 16776704, 7, 245760, 0 },
							{ 43395050, 0, 16776704, 7, 245760, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 37144450, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 43917258, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, -67107785, 0, 35389440 },
							{ 33556224, 0, 16776704, 67002375, 0, 0 },
							{ 33556224, 0, 16776704, 7047, 1, 31457280 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 60688338, 0, 16776704, 7, 245760, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 37537536, 0, 16776704, 7, 196608, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 59639766, 0, 16776704, 7, 245760, 0 },
							{ 37553929, 0, 16776704, 7, 49152, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 43917194, 0, 16776704, 7, 245760, 0 },
							{ 43779962, 0, 16776704, 7, 245760, 0 },
							{ 45942636, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, -512, 7, 0, 504 },
							{ 33556224, 0, 16777214, 7, -1073741824, 8199 },
							{ -33552640, 3, 16776704, 7, 15360, 1536 },
							{ -838859008, -8388608, 16776705, 7, 1006632960, 0 },
							{ 33556224, 1020, 16776704, 7, 3932160, 6144 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 8380416, 16776704, 7, 62914560, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 71, 62, 1006632960 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 7168, 16776704, 15, 0, 245760 },
							{ 33556224, 0, 16776704, 7, 960, -1073741824 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 43386818, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 51849201, 0, 16776704, 7, 196608, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 0, 0, 0, 0, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 39200752, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 60688322, 0, 16776704, 7, 245760, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 },
							{ 33556224, 0, 16776704, 7, 0, 0 } };
	if (1000 <= componentid <= 1191 && 400 <= vehiclemodel <= 611)
	{
		componentid -= 1000;
		vehiclemodel -= 400;

		return (s_LegalMods[vehiclemodel][componentid >>> 5] & 1 << (componentid & 31)) || false;
	}
	return false;
}
