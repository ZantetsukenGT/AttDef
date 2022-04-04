#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_vehicle
	#endinput
#endif
#define _attdef_mod_vehicle

/*
	Vehicle functions hooking
*/

new Iterator: DynamicVehicle<MAX_VEHICLES>; // Array of all spawned vehicles by CreateVehicle only
