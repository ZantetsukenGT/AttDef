#if defined _attdef_cmd_votemenu
	#endinput
#endif
#define _attdef_cmd_votemenu

YCMD: votemenu(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "start a voting (give menu to player)");
	new pID;
	if (sscanf(params, "i", pID))
		return SendUsageMessage(playerid, "/votemenu [Player ID]");

	return PlayerVoteMenu(playerid, pID);
}

PlayerVoteMenu(playerid, onplayerid)
{
	if (Current == -1)
		return SendErrorMessage(playerid, "There's no round in progress!");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You must be playing to be able to vote on this!");

	new votetype = VOTE_TYPE_MENU;
	if (VoteData[votetype][PlayerVoted][playerid])
		return SendErrorMessage(playerid, "You've already voted!");
	if (VoteData[votetype][VoteCount] > 0 && VoteData[votetype][VotingOnPlayer] != onplayerid)
		return SendErrorMessage(playerid, va_return("Another gunmenu-voting is in progress (on playerid: %d), please wait!", VoteData[votetype][VotingOnPlayer]));

	if (!IsPlayerConnected(onplayerid))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (!Player[onplayerid][Playing])
		return SendErrorMessage(playerid, "That player is not playing.");
	if (Player[onplayerid][Team] != ATTACKER && Player[onplayerid][Team] != DEFENDER)
		return SendErrorMessage(playerid, "That player must be part of one of the following teams: Attacker, Defender.");

	// Counting players who are able to vote
	new MaxVotesNeeded = Iter_Count(PlayersInRound);
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
					"{FFFFFF}%s" COL_PRIM " has started {FFFFFF}gunmenu-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/votemenu %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid));
	}
	else
	{
		VoteData[votetype][VoteCount]++;
		VoteData[votetype][PlayerVoted][playerid] = true;
		SendClientMessageToAll(
			-1, va_return(
					"{FFFFFF}%s" COL_PRIM " has added to {FFFFFF}gunmenu-voting " COL_PRIM "on {FFFFFF}%s " COL_PRIM "[%d/%d] [/votemenu %d]", Player[playerid][Name],
					Player[onplayerid][Name], VoteData[votetype][VoteCount], MaxVotesNeeded, onplayerid));
		if (VoteData[votetype][VoteCount] >= MaxVotesNeeded) // Enough people voted!
		{
			SendClientMessageToAll(-1, va_return("" COL_PRIM "Voting result on {FFFFFF}%s: " COL_PRIM "shown gunmenu!", Player[onplayerid][Name]));
			DeletePreciseTimer(VoteData[votetype][VotingExpireTimer]);
			ResetVoting(votetype, false);
			ShowPlayerGunmenu(onplayerid, 0);
		}
	}
	return 1;
}
