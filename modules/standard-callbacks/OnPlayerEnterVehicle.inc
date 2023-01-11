#if defined _attdef_OnPEnterVehicle
	#endinput
#endif
#define _attdef_OnPEnterVehicle

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (Player[playerid][Playing] && Player[playerid][Team] == DEFENDER && !DefendersWithVehicles)
	{
		new Float: x,
			Float: y,
			Float: z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);
	}
	return 1;
}
