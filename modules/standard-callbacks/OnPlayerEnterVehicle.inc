#if defined _attdef_OnPEnterVehicle
	#endinput
#endif
#define _attdef_OnPEnterVehicle

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	Player[playerid][LastEnterVehicleAttempt] = GetTickCount() + 3000;
	return 1;
}
