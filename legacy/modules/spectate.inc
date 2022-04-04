#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_spectate
	#endinput
#endif
#define _attdef_mod_spectate

/*
	Spectator mode
*/

#define UPDATE_SPECINFO_INTERVAL 1000
#define MAX_PLAYER_SPECTATORS	 6 // How many players will be shown
#define SPECTATORS_STRING_SIZE	 (21 + (36 * MAX_PLAYER_SPECTATORS))

new Iterator: AllSpectators<MAX_PLAYERS>;				  // an iterator array that holds all spectators IDs
new Iterator: PlayerSpectators[MAX_PLAYERS]<MAX_PLAYERS>; // an iterator array that holds all player spectators IDs
