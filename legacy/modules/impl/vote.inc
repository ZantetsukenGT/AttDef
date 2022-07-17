#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_vote
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_vote
	#endinput
#endif
#define _attdef_impl_vote

/*
	Vote system
*/

forward ResetVoting(votetype, bool: message);
public ResetVoting(votetype, bool: message)
{
	if (votetype < 0 || votetype >= MAX_VOTE_TYPES)
		return 0;

	if (votetype == VOTE_TYPE_NETCHECK)
	{
		new onplayerid					 = VoteData[votetype][VotingOnPlayer];
		Player[onplayerid][TempNetcheck] = false;
	}
	VoteData[votetype][VoteCount] = 0;
	foreach (new i : Player)
	{
		VoteData[votetype][PlayerVoted][i] = false;
	}
	if (message)
		va_SendClientMessageToAll(
			-1, "{FFFFFF}%s-voting " COL_PRIM "has been reset due to an error or vote timeout (%d secs)!", VoteTypeNames[votetype], VOTE_TIMEOUT_INTERVAL / 1000);
	return 1;
}

InitPlayerVoting(playerid)
{
	for (new i = 0; i < MAX_VOTE_TYPES; i++) { VoteData[i][PlayerVoted][playerid] = false; }
}

InitVoting()
{
	for (new i = 0; i < MAX_VOTE_TYPES; i++) { VoteData[i][VoteCount] = 0; }
}
