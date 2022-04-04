#if defined _attdef_cmd_voteadd
	#endinput
#endif
#define _attdef_cmd_voteadd

YCMD: voteadd(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (add player to round)");

	new pID;
	if (sscanf(params, "i", pID))
		return SendUsageMessage(playerid, "/voteadd [Player ID]");

	return PlayerVoteAdd(playerid, pID);
}

PlayerVoteAdd(playerid, onplayerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There's no round in progress!");

	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "You must be part of one of the following teams: Attacker, Defender.");

	new votetype = VOTE_TYPE_ADD;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");
	if (VoteData[votetype][VoteCount] > 0 && VoteData[votetype][VotingOnPlayer] != onplayerid)
		return SendErrorMessage(playerid, va_return("Another add-voting is in progress (on playerid: %d), please wait!", VoteData[votetype][VotingOnPlayer]));

	if (!IsPlayerConnected(onplayerid))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (Player[onplayerid][Playing])
		return SendErrorMessage(playerid, "That player is already playing.");
	if (Player[onplayerid][InDuel])
		return SendErrorMessage(playerid, "That player is in a duel.");
	if (Player[onplayerid][Team] != ATTACKER && Player[onplayerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "That player must be part of one of the following teams: Attacker, Defender.");

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
		VoteData[votetype][VotingExpireTimer] = SetPreciseTimer("ResetVoting", VOTE_TIMEOUT_INTERVAL, false, "ib", votetype, true);
		VoteData[votetype][VoteCount]		  = 1;
		VoteData[votetype][VotingOnPlayer]	  = onplayerid;
		foreach (new i : Player)
		{
			VoteData[votetype][PlayerVoted][i] = false;
			PlayerPlaySound(i, 1133, 0.0, 0.0, 0.0);
		}
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has started {FFFFFF}add-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/voteadd %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid));
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}add-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/voteadd %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid));
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			SendClientMessageToAll(-1, va_return("" COL_PRIM "Voting result on {FFFFFF}%s: " COL_PRIM "added to the round!", Player[onplayerid][Name]));
			DeletePreciseTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			if (Current != -1)
			{
				if (Player[onplayerid][Spectating])
					StopSpectate(onplayerid);
				if (GameType == BASE)
					AddPlayerToBase(onplayerid);
				else if (GameType == ARENA)
					AddPlayerToArena(onplayerid);
			}
		}
	}
	return 1;
}
