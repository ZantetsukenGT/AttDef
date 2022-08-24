#if defined _attdef_cmd_voteendmatch
	#endinput
#endif
#define _attdef_cmd_voteendmatch

YCMD: voteendmatch(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (end match)");
	return PlayerVoteEndMatch(playerid);
}

PlayerVoteEndMatch(playerid)
{
	if (!WarMode)
		return SendErrorMessage(playerid, "Match mode is already disabled!");
	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "You must be part of one of the following teams: Attacker, Defender.");

	new votetype = VOTE_TYPE_ENDMATCH;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");

	// Counting players who are able to vote
	new countInTeam[2];
	foreach (new i : Player)
	{
		switch (Player[i][Team])
		{
			case ATTACKER: countInTeam[0]++;
			case DEFENDER: countInTeam[1]++;
		}
	}
	if (countInTeam[0] == 0 || countInTeam[1] == 0)
		return SendErrorMessage(playerid, "One team has no active players, so we cannot count this vote.");

	new MaxVotesNeeded = countInTeam[0] + countInTeam[1];
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
					"{FFFFFF}%s" COL_PRIM " has started {FFFFFF}End Match-voting " COL_PRIM "[%d/%d] [/voteendmatch]", Player[playerid][Name], VoteData[votetype][VoteCount],
					MaxVotesNeeded));
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}End Match-voting " COL_PRIM "[%d/%d] [/voteendmatch]", Player[playerid][Name], VoteData[votetype][VoteCount],
					MaxVotesNeeded));
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			SendClientMessageToAll(-1, "" COL_PRIM "End Match-voting result: {FFFFFF}match has been set to end!");
			KillTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			if (Current != -1)
			{
				Current = -1;
				if (RoundPaused)
					TextDrawHideForAll(PauseTD);

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
					if (Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
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

					SpawnPlayer(i);

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

				BaseStarted	 = false;
				ArenaStarted = false;

				SendRconCommand("mapname Lobby");
				FixGamemodeText();
				DeleteAllTeamBars();
				DeleteAllDeadBodies();

				GangZoneDestroy(CPZone);
				CPZone = INVALID_GANG_ZONE;

				GangZoneDestroy(ArenaZone);
				ArenaZone = INVALID_GANG_ZONE;

				ResetTeamLeaders();
				Iter_Clear(PlayersInRound);
			}
			SetTimer("WarEnded", 4000, false);
		}
	}
	return 1;
}
