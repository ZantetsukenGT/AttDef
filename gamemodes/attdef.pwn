
#define DYNAMIC_MEMORY 3500000
#define CGEN_MEMORY 40000
#define MAX_PLAYERS 50
#define YSI_YES_HEAP_MALLOC

#define FOREACH_NO_LOCALS
#define FOREACH_NO_BOTS
#define FOREACH_NO_ACTORS
#define FOREACH_NO_STREAMED

#define NO_TAGS
#include <open.mp>

#include <geoip>		 // A simple library that provide information from IP-API for connected players.
#include <Pawn.RakNet>	 // Allows you to capture and analyze RakNet traffic
#define OPWS_FIX_USE_BSYNC false
#include <opws-fix>		 // 90% bsync (optional), best sniper bug detection
#define WC_CUSTOM_VENDING_MACHINES false
#include <weapon-config> // Provides a more consistent and responsive damage system with many new features.

// YSI Libraries 5.x
// See https://github.com/pawn-lang/YSI-Includes for all the documentation.
#include <YSI_Players\y_groups>	   // Provides an abstraction for various collections of players; including factions, teams, admin levels, and more.
#include <YSI_Coding\y_stringhash> // Performs compile-time hashing of strings, for use as array indexes, case values, and more.
#include <YSI_Coding\y_timers>	   // SetTimer and SetTimerEx wrappers with task and ptask
#include <YSI_Data\y_iterate>	   // The latest version of foreach with many extras for iterators and special iterators (iterator functions).
#include <YSI_Visual\y_commands>   // The most fully featured command processor for SA:MP.
#include <YSI_Visual\y_dialog>	   // Provides an abstraction of dialogs, doing away with IDs and allowing you to use individual public or inline functions per dialog.

// Libraries
#include <sscanf2>	  // Sscanf 2.11.x
#include <progress2>  // A SA:MP UI library for rendering progress bars
//#include <mSelection> // Selection with preview models feature library
#include <gBugFix>	  // Fix false vehicle entry as passenger (G (teleport/distance) bug)
#include <md-sort>	  // Sorts multi dimensional arrays by Slice (Oscar Broman)
#define MAPFIX_USE_STREAMER false
#include <mapfix>	   // Texture bug fixes of the GTA San Andreas map such as passing through some walls, windows, floors etc.
#include <samp_bcrypt> // A bcrypt plugin for samp in Rust.
#include <dyn-dialog-pages> // https://github.com/ZantetsukenGT/samp-dyn-dialog-pages

// Att-Def's own stuff
//#tryinclude <player-conns> // used for external services, more specifically, used for a iptables whitelist orchestrated by a NodeJS project
//#tryinclude <pwac>
#include <fps-utils>
#include <fake-ping>
#include <anti-secrets>
#include <vehicle-freeze>
#include <modules>
//#include <anims-broadcast> // experimenting with anim broadcasting, stun animations, more specifically 
#include <commands>
#include <wc-callbacks>		  // Weapon-config's callback handling
#include <other-callbacks>	  // Dependencies and miscellaneous callbacks, organized in different files
#include <standard-callbacks> // SA-MP default callbacks, organized in different files, must be the last include

/*
	Useful resources:
	* https://open.mp/docs/scripting/resources/limits

	Tips:
	* include y_hooks in every file a `hook` keyword is used, and make it the last include.
	* use y_va functions instead of slice's strlib ones.
*/

main() {}
