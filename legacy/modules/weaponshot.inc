#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_weaponshot
	#endinput
#endif
#define _attdef_mod_weaponshot

/*
	Weapon shots handler
	Mostly used for damage bubbles and wc wrappers`
*/

#define DAMAGE_BUBBLE_STRING_LENGTH 1024					 // Taken damage bubble string length
#define HIDE_DAMAGE_TEXTDRAW_AFTER	3000					 // Time needed to hide visual damage textdraw (milliseconds)

#define GRENADE_HIGH_DAMAGE			16.0					// Modified grenade damage
#define GRENADE_MEDIUM_DAMAGE		GRENADE_HIGH_DAMAGE / 2 // Modified grenade damage
#define GRENADE_LOW_DAMAGE			GRENADE_HIGH_DAMAGE / 3 // Modified grenade damage

new FriendlyDamageTimer[MAX_PLAYERS];

new Float: DamageBubbleDMG[MAX_PLAYERS][MAX_PLAYERS];
new DamageBubbleWeapon[MAX_PLAYERS][MAX_PLAYERS];
new DamageBubbleLastTick[MAX_PLAYERS][MAX_PLAYERS];
new Iterator: PlayerDMGBubble<MAX_PLAYERS, MAX_PLAYERS>;  // Holds players having bubble's and their damagers
