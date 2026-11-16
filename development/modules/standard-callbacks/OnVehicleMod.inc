#if defined _attdef_OnVMod
	#endinput
#endif
#define _attdef_OnVMod

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if (!IsVehicleComponentLegal(GetVehicleModel(vehicleid), componentid))
		return 0;
	return 1;
}
