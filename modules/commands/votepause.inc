#if defined _attdef_cmd_votepause
	#endinput
#endif
#define _attdef_cmd_votepause

YCMD: votepause(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (pause round)");
	return PlayerVotePause(playerid);
}

PlayerVotePause(playerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There's no round in progress!");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You must be playing to be able to vote on this!");

	new votetype = VOTE_TYPE_PAUSE;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");
	if (RoundPaused)
		return SendErrorMessage(playerid, "Round is already paused.");

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
		va_SendClientMessageToAll(
			-1, "{FFFFFF}%s" COL_PRIM " has started {FFFFFF}pause-voting " COL_PRIM "[%d/%d] [/votepause or press Y]", Player[playerid][Name], VoteData[votetype][VoteCount],
					MaxVotesNeeded);
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		va_SendClientMessageToAll(
			-1, "{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}pause-voting " COL_PRIM "[%d/%d] [/votepause or press Y]", Player[playerid][Name], VoteData[votetype][VoteCount],
					MaxVotesNeeded);
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			SendClientMessageToAll(-1, "" COL_PRIM "Pause-voting result: {FFFFFF}round has been paused!");
			KillTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			PausePressed = GetTickCount();
			PauseRound();
		}
	}
	return 1;
}
