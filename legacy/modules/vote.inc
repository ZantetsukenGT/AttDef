#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_vote
	#endinput
#endif
#define _attdef_mod_vote

/*
	Vote system
*/

#define VOTE_TIMEOUT_INTERVAL 30000

// Vote types
enum
{
	VOTE_TYPE_PAUSE,
	VOTE_TYPE_UNPAUSE,
	VOTE_TYPE_ADD,
	VOTE_TYPE_READD,
	VOTE_TYPE_REM,
	VOTE_TYPE_KICK,
	VOTE_TYPE_NETCHECK,
	VOTE_TYPE_ENDMATCH,
	VOTE_TYPE_RESTARTROUND,
	VOTE_TYPE_SWITCH,
	VOTE_TYPE_MENU,

	MAX_VOTE_TYPES = 11 // How many vote types we have
}

enum VoteData_STRUCT {
	bool: PlayerVoted[MAX_PLAYERS], // Whether a player voted or not
	VoteCount,						// How many votes we got
	VotingOnPlayer,					// On whom is this voting?
	VotingExpireTimer				// A timer for voting expiration
}

// Vote types names
new VoteTypeNames[MAX_VOTE_TYPES][]
	= { "Pause", "Unpause", "Add", "Readd", "Rem", "Kick", "NetCheck", "Match-End", "Restart-Round", "Team-Switch", "Gunmenu-show" };

new VoteData[MAX_VOTE_TYPES][VoteData_STRUCT];
