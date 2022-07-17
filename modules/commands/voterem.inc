#if defined _attdef_cmd_voterem
	#endinput
#endif
#define _attdef_cmd_voterem

YCMD: voterem(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (remove a player from round)");
	new pID;
	if (sscanf(params, "i", pID))
		return SendUsageMessage(playerid, "/voterem [Player ID]");

	return PlayerVoteRem(playerid, pID);
}

PlayerVoteRem(playerid, onplayerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There's no round in progress!");

	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "You must be part of one of the following teams: Attacker, Defender.");

	new votetype = VOTE_TYPE_REM;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");
	if (VoteData[votetype][VoteCount] > 0 && VoteData[votetype][VotingOnPlayer] != onplayerid)
		return SendErrorMessage(playerid, va_return("Another rem-voting is in progress (on playerid: %d), please wait!", VoteData[votetype][VotingOnPlayer]));

	if (!IsPlayerConnected(onplayerid))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[onplayerid][Playing])
		return SendErrorMessage(playerid, "This player is not even playing!");

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
		foreach (new i : Player)
		{
			VoteData[votetype][PlayerVoted][i] = false;
			PlayerPlaySound(i, 1133, 0.0, 0.0, 0.0);
		}
		VoteData[votetype][PlayerVoted][playerid] = true;
		va_SendClientMessageToAll(
			-1, "{FFFFFF}%s" COL_PRIM " has started {FFFFFF}rem-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/voterem %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid);
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		va_SendClientMessageToAll(
			-1, "{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}rem-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/voterem %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid);
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			va_SendClientMessageToAll(-1, COL_PRIM "Voting result on {FFFFFF}%s: " COL_PRIM "removed from the round!", Player[onplayerid][Name]);
			KillTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			if (Current != -1)
			{
				RemovePlayerFromRound(onplayerid);
			}
		}
	}
	return 1;
}
