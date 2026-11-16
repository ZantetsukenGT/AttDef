#if defined _attdef_cmd_voterr
	#endinput
#endif
#define _attdef_cmd_voterr

YCMD: voterr(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (restart round)");
	return PlayerVoteRestartRound(playerid);
}

PlayerVoteRestartRound(playerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There's no round in progress!");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You must be playing to be able to vote on this!");

	new votetype = VOTE_TYPE_RESTARTROUND;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");

	// Counting players who are able to vote
	new MaxVotesNeeded = Iter_Count(PlayersInRound);
	if (VoteData[votetype][VoteCount] < 1) // First vote?
	{
		VoteData[votetype][VotingExpireTimer] = SetTimerEx("ResetVoting", VOTE_TIMEOUT_INTERVAL, false, "ib", votetype, true);
		VoteData[votetype][VoteCount]		  = 1;
		foreach (new i : Player)
		{
			VoteData[votetype][PlayerVoted][i] = false;
			PlayerPlaySound(i, 1133, 0.0, 0.0, 0.0);
		}
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has started {FFFFFF}restart round-voting " COL_PRIM "[%d/%d] [/voterr]", Player[playerid][Name], VoteData[votetype][VoteCount],
					MaxVotesNeeded));
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}restart round-voting " COL_PRIM "[%d/%d] [/voterr", Player[playerid][Name], VoteData[votetype][VoteCount],
					MaxVotesNeeded));
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			AllowStartBase = false;
			SendClientMessageToAll(-1, "" COL_PRIM "Restart round-voting result: {FFFFFF}round has been set to restart!");
			KillTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			if (RoundPaused)
			{
				TextDrawHideForAll(PauseTD);
				RoundPaused = false;
			}
			RoundUnpausing = false;

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
					Player[i][WasInTeam]	= NON;

					Player[i][WasInBase]	= false;
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
				HideRoundStats(i);
			}

			GangZoneDestroy(CPZone);
			CPZone = INVALID_GANG_ZONE;

			GangZoneDestroy(ArenaZone);
			ArenaZone = INVALID_GANG_ZONE;

			TextDrawHideForAll(EN_CheckPoint);
			TextDrawHideForAll(CheckpointWarningBox);
		}
	}
	return 1;
}
