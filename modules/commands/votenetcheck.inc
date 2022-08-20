#if defined _attdef_cmd_votenetcheck
	#endinput
#endif
#define _attdef_cmd_votenetcheck

YCMD: votenetcheck(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (toggle netcheck on a player)");
	new pID;
	if (sscanf(params, "r", pID))
		return SendUsageMessage(playerid, "/votenetcheck [Player Name/ID]");

	return PlayerVoteNetCheck(playerid, pID);
}

PlayerVoteNetCheck(playerid, onplayerid)
{
	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "You must be part of one of the following teams: Attacker, Defender.");

	new votetype = VOTE_TYPE_NETCHECK;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");
	if (VoteData[votetype][VoteCount] > 0 && VoteData[votetype][VotingOnPlayer] != onplayerid)
		return SendErrorMessage(playerid, va_return("Another netcheck-voting is in progress (on playerid: %d), please wait!", VoteData[votetype][VotingOnPlayer]));

	if (playerid == onplayerid)
		return SendErrorMessage(playerid, "You cannot vote to netcheck yourself. Try to ask people to vote netcheck you instead!");

	if (onplayerid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player is not connected.");

	// Counting players who are able to vote
	new countInTeam[2];
	foreach (new i : Player)
	{
		if (i == onplayerid)
			continue;

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
		VoteData[votetype][VotingOnPlayer]	  = onplayerid;
		Player[onplayerid][TempNetcheck]	  = true;
		foreach (new i : Player)
		{
			VoteData[votetype][PlayerVoted][i] = false;
			PlayerPlaySound(i, 1133, 0.0, 0.0, 0.0);
		}
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has started {FFFFFF}netcheck-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/votenetcheck %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid));
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}netcheck-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/votenetcheck %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid));
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			if (Player[onplayerid][NetCheck])
			{
				Player[onplayerid][NetCheck]  = false;
				Player[onplayerid][FPSCheck]  = false;
				Player[onplayerid][PingCheck] = false;
				Player[onplayerid][PLCheck]	  = false;
				SendClientMessageToAll(-1, va_return("" COL_PRIM "Voting result on {FFFFFF}%s: " COL_PRIM "disabled Net-Check!", Player[onplayerid][Name]));
				db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET NetCheck = 0 WHERE Name = '%q'", Player[onplayerid][Name])));
			}
			else
			{
				Player[onplayerid][NetCheck]  = true;
				Player[onplayerid][FPSCheck]  = true;
				Player[onplayerid][PingCheck] = true;
				Player[onplayerid][PLCheck]	  = true;
				SendClientMessageToAll(-1, va_return("" COL_PRIM "Voting result on {FFFFFF}%s: " COL_PRIM "enabled Net-Check!", Player[onplayerid][Name]));
				db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET NetCheck = 1 WHERE Name = '%q'", Player[onplayerid][Name])));
			}
			KillTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
		}
	}
	return 1;
}
