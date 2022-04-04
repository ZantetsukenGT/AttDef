#if defined _attdef_cmd_voteunpause
	#endinput
#endif
#define _attdef_cmd_voteunpause

YCMD: voteunpause(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (pause round)");
	return PlayerVoteUnpause(playerid);
}

PlayerVoteUnpause(playerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There's no round in progress!");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You must be playing to be able to vote on this!");

	new votetype = VOTE_TYPE_UNPAUSE;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");
	if (!RoundPaused)
		return SendErrorMessage(playerid, "Round is already running and is not paused.");

	// Counting players who are able to vote
	new MaxVotesNeeded = Iter_Count(PlayersInRound);
	if (VoteData[votetype][VoteCount] < 1) // First vote?
	{
		VoteData[votetype][VotingExpireTimer] = SetPreciseTimer("ResetVoting", VOTE_TIMEOUT_INTERVAL, false, "ib", votetype, true);
		VoteData[votetype][VoteCount]		  = 1;
		foreach (new i : Player)
		{
			VoteData[votetype][PlayerVoted][i] = false;
			PlayerPlaySound(i, 1133, 0.0, 0.0, 0.0);
		}
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has started {FFFFFF}unpause-voting " COL_PRIM "[%d/%d] [/voteunpause or press Y]", Player[playerid][Name],
					VoteData[votetype][VoteCount], MaxVotesNeeded));
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}unpause-voting " COL_PRIM "[%d/%d] [/voteunpause or press Y]", Player[playerid][Name],
					VoteData[votetype][VoteCount], MaxVotesNeeded));
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			DeletePreciseTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			if (RoundUnpausing)
				return SendClientMessageToAll(-1, "" COL_PRIM "Unpause-voting result: {FFFFFF}round is already being unpaused!");

			PauseCountdown = 4;
			UnpauseRound();
			SendClientMessageToAll(-1, "" COL_PRIM "Unpause-voting result: {FFFFFF}round has been unpaused!");
		}
	}
	return 1;
}
