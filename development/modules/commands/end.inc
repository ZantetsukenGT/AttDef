#if defined _attdef_cmd_end
	#endinput
#endif
#define _attdef_cmd_end

YCMD: end(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 3 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "kill the currently active round.");
	if (AlreadyEndingRound)
		return SendErrorMessage(playerid, "Please wait.");
	if (Current == -1 && AllowStartBase)
		return SendErrorMessage(playerid, "Round is not active.");

	if (PreStartRoundTimer)
	{
		KillTimer(PreStartRoundTimer);
		PreStartRoundTimer = 0;
	}
	if (ViewRoundTimer)
	{
		KillTimer(ViewRoundTimer);
		ViewRoundTimer = 0;

		TextDrawSetString(centerTeamNames, " ");
		TextDrawSetString(AttDef_RoundTimer, " ");
		TextDrawSetString(AttDef_ModernRoundStats[5], " ");
	}

	Current = -1;
	AllowStartBase = true;
	if (RoundPaused)
		TextDrawHideForAll(PauseTD);

	GangZoneDestroy(CPZone);
	CPZone = INVALID_GANG_ZONE;

	GangZoneDestroy(ArenaZone);
	ArenaZone = INVALID_GANG_ZONE;

	RoundPaused			   = false;
	TeamCapturingCP		   = NON;
	PlayersInCP			   = 0;

	PlayersAlive[ATTACKER] = 0;
	PlayersAlive[DEFENDER] = 0;

	PlayersDead[ATTACKER]  = 0;
	PlayersDead[DEFENDER]  = 0;

	RoundUnpausing		   = false;

	foreach (new i : Player)
	{
		if (Player[i][InDM] || Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
			continue;

		Player[i][Playing] = false;
		Player[i][WasInCP] = false;
		if (Player[i][Spectating])
			StopSpectate(i);
		Player[i][WasInBase]	= false;
		Player[i][WasInTeam]	= NON;
		Player[i][WeaponPicked] = 0;
		Player[i][TimesSpawned] = 0;

		TogglePlayerControllable(i, 0);
		RemovePlayerMapIcon(i, 59);

		SpawnInLobby(i);

		DisablePlayerCheckpoint(i);
		SetPlayerScore(i, 0);
		HidePlayerDialog(i);

		PlayerTextDrawHide(i, AreaCheckTD[i]);
		PlayerTextDrawHide(i, AreaCheckBG[i]);
	}

	foreach (new i : Player)
	{
		HideRoundStats(i);
	}
	TextDrawHideForAll(EN_CheckPoint);
	TextDrawHideForAll(CheckpointWarningBox);

	ResetGunmenuSelections();
	ResetBackupRequests();

	BaseStarted	 = false;
	ArenaStarted = false;

	SendRconCommand("mapname Lobby");
	//FixGamemodeText();

	DeleteAllTeamBars();
	HideTeamCornerInfoForAll();

	DeleteAllDeadBodies();

	GangZoneDestroy(CPZone);
	CPZone = INVALID_GANG_ZONE;
	
	GangZoneDestroy(ArenaZone);
	ArenaZone = INVALID_GANG_ZONE;

	ResetTeamLeaders();
	Iter_Clear(PlayersInRound);

	if (AutoRoundStarter)
		SetRoundAutoStart(20);

	LogAdminCommand("end", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has ended the round.", Player[playerid][Name]);
}
