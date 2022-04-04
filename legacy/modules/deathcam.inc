#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_deathcam
	#endinput
#endif
#define _attdef_mod_deathcam

/*
	Death camera script
*/

#define DEATH_CAMERA_DURATION 7000 // Duration of death camera views (in milliseconds)
