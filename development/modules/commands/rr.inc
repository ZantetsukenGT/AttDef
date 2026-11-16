#if defined _attdef_cmd_rr
	#endinput
#endif
#define _attdef_cmd_rr

YCMD: rr(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "restart a round.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");

	AllowStartBase = false;
	if (RoundPaused)
		TextDrawHideForAll(PauseTD);
	RoundPaused	   = false;
	RoundUnpausing = false;

	GangZoneDestroy(CPZone);
	CPZone = INVALID_GANG_ZONE;

	GangZoneDestroy(ArenaZone);
	ArenaZone = INVALID_GANG_ZONE;

	ResetBackupRequests();

	new iString[128];
	format(iString, sizeof(iString), "%s " COL_PRIM "has set the round to restart.", Player[playerid][Name]);
	SendClientMessageToAll(-1, iString);

	ResetGunmenuSelections();

	if (GameType == BASE)
	{
		BaseStarted = false;
		PreStartRoundTimer = SetTimerEx("OnBaseStart", 4000, false, "i", Current);
	}
	else if (GameType == ARENA)
	{
		ArenaStarted = false;
		PreStartRoundTimer = SetTimerEx("OnArenaStart", 4000, false, "i", Current);
	}

	foreach (new i : Player)
	{
		if (Player[i][OnGunmenu])
			HidePlayerGunmenu(i);
		if (CanPlay(i))
		{
			if (Player[i][Spectating])
				StopSpectate(i);
			Player[i][WasInCP]		= false;

			Player[i][WasInBase]	= false;
			Player[i][WasInTeam]	= NON;
			Player[i][WeaponPicked] = 0;
			Player[i][TimesSpawned] = 0;

			HidePlayerDialog(i);
			DisablePlayerCheckpoint(i);
			RemovePlayerMapIcon(i, 59);

			PlayerTextDrawHide(i, AreaCheckTD[i]);
			PlayerTextDrawHide(i, AreaCheckBG[i]);
			TogglePlayerControllable(i, 0);
			Player[i][ToAddInRound] = true;
		}
	}

	foreach (new i : Player)
	{
		HideRoundStats(i);
	}
	TextDrawHideForAll(EN_CheckPoint);
	TextDrawHideForAll(CheckpointWarningBox);
	return 1;
}
