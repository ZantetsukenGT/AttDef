#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_colors
	#endinput
#endif
#define _attdef_mod_colors

/*
	Gamemode colors: teams, messages... etc
*/

#include "modules/this_core.inc"

// Teams colors
#define ATTACKER_PLAYING	 0xFF003355 // Bright red color with 55 transparency (Range 00 - 99 - FF)
#define ATTACKER_NOT_PLAYING 0xFF555555 // Orange red color
#define ATTACKER_SUB_COLOR	 0xFFAAAA55 // Yello red color
#define DEFENDER_PLAYING	 0x3344FF55 // Bright blue color
#define DEFENDER_NOT_PLAYING 0x3377FF55 // Light blue color
#define DEFENDER_SUB_COLOR	 0xAAAAFF55 // Very light blue color
#define REFEREE_COLOR		 0xFFFF0055 // Bright Yellow color
#define ATTACKER_ASKING_HELP 0xFF777788 // Orange red color
#define DEFENDER_ASKING_HELP 0x7777FF88 // Light blue color
#define ATTACKER_TEAM_LEADER 0xFF53FF88 // Bright Pink color
#define DEFENDER_TEAM_LEADER 0x00A8FF88 // Aqua color

// GangZone colors
#define GANGZONE_ARENA		 0x95000099 // Red
#define GANGZONE_CPARENA	 0x00000033 // Black Transperent
#define GANGZONE_CP			 0x4444FF99 // Blue
#define GANGZONE_FLASH		 0xFF222299 // Flash color when CP is being taken (Red)

// Client message color
#define COL_PRIM_HEX		 0x01A2F8FF // Primary color used in client messages as integer
#define COL_ERROR_HEX		 0xFF3333FF // Color used in cmd error messages as integer
#define COL_WARNING_HEX		 0xFFCC00FF // Color used in cmd warning messages as integer
#define COL_USAGE_HEX		 0xCCCCCCFF // Color used in cmd usage messages as integer
#define COL_TIP_PRIM_HEX	 0xFFEEB5FF // This color is used in tips messages as integer
#define COL_PRIM			 "{01A2F8}" // Primary color used in client messages
#define COL_SEC				 "{FFFFFF}" // Secondary color used in client messages
#define COL_ERROR			 "{FF3333}" // Color used in cmd error messages
#define COL_WARNING			 "{FFCC00}" // Color used in cmd warning messages
#define COL_USAGE			 "{CCCCCC}" // Color used in cmd usage messages
#define COL_TIP_PRIM		 "{FFEEB5}" // This color is used in tips messages
#define COL_TIP				 "{FFC400}" // This color is used in tips messages
#define COL_AC				 "{F51414}" // Colors for zyph's AC scripts

// Team text colors
new TextColor[MAX_TEAMS][10];
new TDC[MAX_TEAMS][13];

// Server theme (textdraws) color
new MAIN_BACKGROUND_COLOUR;
new MAIN_TEXT_COLOUR[16]; // = "~w~";
new ColScheme[10] = COL_PRIM;

//themes
new ServerName[50];
