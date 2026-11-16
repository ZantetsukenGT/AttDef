#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_teamhpbars
	#endinput
#endif
#define _attdef_mod_teamhpbars

/*
	Team HP Bars
*/

#include <sscanf2> // Sscanf 2.10.x

// Team bars constant co-ordinates
#define TEAMBARS_BAR_START_X		 557.00
#define TEAMBARS_BAR_START_Y		 418.00
#define TEAMBARS_TEXT_START_X		 559.00
#define TEAMBARS_DIFF_Y				 14.00
#define TEAMBARS_ATTACKER_COLOR		 0xFF6A5622
#define TEAMBARS_DEFENDER_COLOR		 0x7C6DE822
#define TEAMBARS_ATTACKER_HELP_COLOR 0xFF919322
#define TEAMBARS_DEFENDER_HELP_COLOR 0x9DF9FF22

enum TeamBarsDataStruct {
	PlayerBar: TeamBar, // The progress bar that shows player health and armour for team
	Text: TeamBarText,	// The text that shows his name, damage and total hp for team
	Float: TeamBar_Y,	// His bar textdraws Y co-ordinates
	TeamBar_Team		// What team this bar is shown to
}

new TeamBarsData[MAX_PLAYERS][TeamBarsDataStruct];
new Iterator: PlayerWithTeamBar<MAX_PLAYERS>;				   // This array is gonna hold IDs of players who got team bars created for them
new bool: TeamBarShownForPlayer[MAX_PLAYERS][MAX_PLAYER_BARS]; // Gonna tell whether a team bar is shown to a player or not
