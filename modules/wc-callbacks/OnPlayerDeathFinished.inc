#if defined _attdef_OnPDeathFinished
	#endinput
#endif
#define _attdef_OnPDeathFinished

public OnPlayerDeathFinished(playerid)
{
	if (Player[playerid][Playing])
	{
		if (Player[playerid][CouldShowDeathQuote]) // if weapon is not knife and death camera system is not disabled
		{
			new Float: x,
				Float: y,
				Float: z;
			GetPlayerPos(playerid, x, y, z);
			PlayDeathCamera(playerid, x, y, z, Player[playerid][ShowDeathQuote]);
		}
		else // If not
			SpectateAnyPlayerT(playerid);
	}
	else if (Player[playerid][InDuel])
		ProcessDuellerDeath(playerid);

	// Hide arena out of bound warning textdraws if they're shown
	if (Player[playerid][OutOfArena] != MAX_ZONE_LIMIT_WARNINGS)
	{
		PlayerTextDrawHide(playerid, AreaCheckTD[playerid]);
		PlayerTextDrawHide(playerid, AreaCheckBG[playerid]);
	}
	Player[playerid][InDM]	  = false;
	Player[playerid][Playing] = false;
	SetPlayerScore(playerid, 0);
	Iter_Remove(PlayersInRound, playerid);
	UpdateTeamPlayerCount(Player[playerid][Team], true, playerid);
	UpdateTeamHP(Player[playerid][Team], playerid);
	// Handle spectate
	foreach (new i : AllSpectators)
	{
		if (Player[i][IsSpectatingID] == playerid)
		{
			if (Player[i][Team] == REFEREE)
				SpectateAnyPlayer(i, false, true, playerid);
			else
				SpectateAnyPlayer(i, true, true, playerid);
		}
	}

	// If they're selecting from gunmenu
	if (Player[playerid][OnGunmenu])
	{
		// Hide it!!!
		HidePlayerGunmenu(playerid);
	}

	// Reset player gunmenu selections
	ResetPlayerGunmenu(playerid, false);

	// Call OnPlayerLeaveCheckpoint to see if player was in CP and fix issues
	CallLocalFunction("OnPlayerLeaveCheckpoint", "i", playerid);

	// If he's spectating, stop it
	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	if (!Player[playerid][InDeathCamera])
	{
		// If they're in a DM
		if (Player[playerid][DMReadd] > 0)
		{
			GetPlayerPos(playerid, Player[playerid][DmPosX], Player[playerid][DmPosY], Player[playerid][DmPosZ]);
			GetPlayerFacingAngle(playerid, Player[playerid][DmAngle]);
			// Re-spawn them there
			SpawnInDM(playerid, Player[playerid][DMReadd]);
		}
		else // Spawn player in a lobby
			SpawnInLobby(playerid);
	}
	return 1;
}
