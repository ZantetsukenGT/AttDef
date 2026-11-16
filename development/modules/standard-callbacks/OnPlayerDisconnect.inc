#if defined _attdef_OnPDisconnect
	#endinput
#endif
#define _attdef_OnPDisconnect

public OnPlayerDisconnect(playerid, reason)
{
	switch (reason)
	{
		case 0:
		{
			if (!Player[playerid][Playing])
				va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}has had a crash/timeout.", Player[playerid][Name]);
			else
				va_SendClientMessageToAll(
					-1, "{FFFFFF}%s {CCCCCC}has had a crash/timeout {FFFFFF}(HP %d | AP %d).", Player[playerid][Name], GetHP(playerid),
					GetAP(playerid));
		}
		case 1:
		{
			if (!Player[playerid][Playing])
				va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}has quit the server.", Player[playerid][Name]);
			else
				va_SendClientMessageToAll(
					-1, "{FFFFFF}%s {CCCCCC}has quit the server {FFFFFF}(HP %d | AP %d).", Player[playerid][Name], GetHP(playerid),
					GetAP(playerid));
		}
		case 2:
		{
			if (!Player[playerid][Playing])
				va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}has been kicked or banned.", Player[playerid][Name]);
			else
				va_SendClientMessageToAll(
					-1, "{FFFFFF}%s {CCCCCC}has been kicked or banned {FFFFFF}(HP %d | AP %d).", Player[playerid][Name], GetHP(playerid),
					GetAP(playerid));
		}
	}
	// Check player spawned vehicle

	new vehicleid = Player[playerid][LastVehicle];
	if (vehicleid)
	{
		foreach (new i : VehicleDriver(vehicleid))
		{
			RemovePlayerFromVehicle(i);
		}
		foreach (new i : VehiclePassenger(vehicleid))
		{
			RemovePlayerFromVehicle(i);
		}
		DestroyVehicle(vehicleid);
		Player[playerid][LastVehicle] = 0;
	}
	// Fixes the x Vs y textdraws with current team player count
	FixVsTextDraw(playerid);
	return 1;
}
