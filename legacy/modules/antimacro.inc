#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_antimacro
	#endinput
#endif
#define _attdef_mod_antimacro
/*
	Anti sprint macro script
*/

// Core
#define ANTIMACRO_MAX_WARNINGS		   3   // Maximum warnings, punishment after that
#define ANTIMACRO_MIN_SPEED			   40  // We don't need to check a player for macros if he's sprinting with such a speed
#define ANTIMACRO_MIN_SPEED_DIFF	   0   // A player may not be checked for macros if the difference between his old speed and new speed is below this
#define ANTIMACRO_SPRINT_KEY_LIMIT	   65  // Least acceptable time difference between each sprint key hit (in milliseconds)
#define ANTIMACRO_FORGET_WARNING_AFTER 900 // Reset macro check variables after this time (milliseconds). 0 to forget immediately

// Options
#define ANTIMACRO_BADNET_CHECK		   0 // 0 disable. If set to 1, antimacro will check player's net before checking sprint macros

#if ANTIMACRO_BADNET_CHECK == 1
	// Net check settings
	#define ANTIMACRO_PACKETLOSS 1.5 // Dangerous packetloss, could cause false positive
#endif

enum ANTIMACRO_DATA_STRUCTURE
{
	LastTimeSprinted,	// Last time (tick count?) player pressed the sprint key
	LastMonitoredSpeed, // Last monitored speed by the server
	TimesWarned,		// How many times warned
	LastTimeWarned		// When the last warning was
}

new AntimacroData[MAX_PLAYERS][ANTIMACRO_DATA_STRUCTURE];
