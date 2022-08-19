#if defined _attdef_OnPExitVehicle
	#endinput
#endif
#define _attdef_OnPExitVehicle

public OnPlayerExitVehicle(playerid, vehicleid)
{
	Player[playerid][LastEnterVehicleAttempt] = GetTickCount() - 5000;
	return 1;
}
