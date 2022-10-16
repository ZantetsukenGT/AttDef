#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_fightstyle
	#endinput
#endif
#define _attdef_mod_fightstyle

/*
	Fightstyle script
*/

new FightStyleIDs[6]	   = { 4, 5, 6, 7, 15, 16 };

new FightStyleNames[6][11] = { "Normal", "Boxing", "KungFu", "Knee-head", "Grab-kick", "Elbow-kick" };
