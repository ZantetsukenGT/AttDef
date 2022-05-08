#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_weaponshot
	#endinput
#endif
#define _attdef_mod_weaponshot

/*
	Weapon damage textdraws handler
*/

#define HIDE_DAMAGE_TEXTDRAW_AFTER	5000					 // Time needed to hide visual damage textdraw (milliseconds)

#define GRENADE_HIGH_DAMAGE			16.0					// Modified grenade damage
#define GRENADE_MEDIUM_DAMAGE		GRENADE_HIGH_DAMAGE / 2 // Modified grenade damage
#define GRENADE_LOW_DAMAGE			GRENADE_HIGH_DAMAGE / 3 // Modified grenade damage

new FriendlyDamageTimer[MAX_PLAYERS];
