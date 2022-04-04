#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_vehicle
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/hooking/' folder."
#endif

#if defined _attdef_impl_vehicle
	#endinput
#endif
#define _attdef_impl_vehicle

/*
	Vehicle functions hooking
*/

#include <YSI_Coding\y_hooks>

hook stock CreateVehicle(modelid, Float: spawn_x, Float: spawn_y, Float: spawn_z, Float: angle, color1, color2, respawn_delay, bool: addsiren = false)
{
	new createdVehicleID = continue(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay, addsiren);
	if (createdVehicleID != INVALID_VEHICLE_ID)
		Iter_Add(DynamicVehicle, createdVehicleID);

	return createdVehicleID;
}

// IMPORTANT NOTE
// IF YOU'RE GOING TO USE RemoveVehicle IN A LOOP
// OVER DynamicVehicle ITERATOR ARRAY
// MAKE remove AS FALSE, NOT TRUE
// AND USE Iter_Clear(DynamicVehicle) RIGHT AFTER
// THE LOOP IS FINISHED, THAT'S MUCH SAFER

stock RemoveVehicle(vehicleid, bool: remove = true)
{
	new didDestroy = DestroyVehicle(vehicleid);
	if (didDestroy && remove)
		Iter_Remove(DynamicVehicle, vehicleid);

	return didDestroy;
}
