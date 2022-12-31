#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_this_core
	#endinput
#endif
#define _attdef_mod_this_core

/*
	Gamemode core
*/

#include <mSelection> // Selection with preview models feature library

#define GM_VERSION "1.38.0 (r)"
#define GM_NAME	   "Att-Def"
new GM_WEBSITE[50] = "discord.io/attackdefend";

#define SAFE_GAMETEXT_AUTO_CHECK 0 // When enabled, most of textdraw and gametext functions are hooked to automatically reject unsafe use of tildes.

// Limits
#define MAX_TEAMS				 6
#define MAX_CHANNELS			 cellmax
#define DRAW_DISTANCE			 25
#define MAX_INI_ENTRY_TEXT		 80

new DB: sqliteconnection; // SQLite Databases
new teamskinlist = mS_INVALID_LISTID, playerskinlist = mS_INVALID_LISTID;
new stock bool: IsSkinshot = false;
