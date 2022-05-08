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
					-1, "{FFFFFF}%s {CCCCCC}has had a crash/timeout {FFFFFF}(HP %.1f | AP %.1f).", Player[playerid][Name], GetPlayerHealth(playerid), GetPlayerArmour(playerid));
		}
		case 1:
		{
			if (!Player[playerid][Playing])
				va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}has quit the server.", Player[playerid][Name]);
			else
				va_SendClientMessageToAll(
					-1, "{FFFFFF}%s {CCCCCC}has quit the server {FFFFFF}(HP %.1f | AP %.1f).", Player[playerid][Name], GetPlayerHealth(playerid), GetPlayerArmour(playerid));
		}
		case 2:
		{
			if (!Player[playerid][Playing])
				va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}has been kicked or banned.", Player[playerid][Name]);
			else
				va_SendClientMessageToAll(
					-1, "{FFFFFF}%s {CCCCCC}has been kicked or banned {FFFFFF}(HP %.1f | AP %.1f).", Player[playerid][Name], GetPlayerHealth(playerid), GetPlayerArmour(playerid));
		}
	}
	// Check player spawned vehicle
	if (IsValidVehicle(Player[playerid][LastVehicle]))
	{
		foreach (new i : Player)
		{
			if (i == playerid)
				continue;

			if (GetPlayerVehicleID(i) == Player[playerid][LastVehicle])
				goto DoNotDestroyVehicle;
		}
		RemoveVehicle(Player[playerid][LastVehicle]);
		Player[playerid][LastVehicle] = -1;
	DoNotDestroyVehicle:
	}
	// Fixes the x Vs y textdraws with current team player count
	FixVsTextDraw(playerid);
	return 1;
}
