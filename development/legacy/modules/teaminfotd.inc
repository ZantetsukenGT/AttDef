#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_teaminfotd
	#endinput
#endif
#define _attdef_mod_teaminfotd

/*
	Team information on the right corner
*/

enum _sort_Info_
{
	playerID,
	Float: playerDamage
}

#define MAX_PLAYERS_IN_TEXTDRAW 4
#define MAX_PLAYERS_STRING_SIZE 255

new Text: TeamCornerInfoFirstTD[2];
new Text: TeamCornerInfoSecondTD[2];
