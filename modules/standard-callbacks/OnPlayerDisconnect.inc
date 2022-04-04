#if defined _attdef_OnPDisconnect
	#endinput
#endif
#define _attdef_OnPDisconnect

public OnPlayerDisconnect(playerid, reason)
{
	// Send public disconnect messages
	new iString[144];
	switch (reason)
	{
		case 0:
		{
			if (!Player[playerid][Playing])
				format(iString, sizeof(iString), "{FFFFFF}%s {CCCCCC}has had a crash/timeout.", Player[playerid][Name]);
			else
				format(
					iString, sizeof(iString), "{FFFFFF}%s {CCCCCC}has had a crash/timeout {FFFFFF}(HP %d | AP %d).", Player[playerid][Name], Player[playerid][pHealth],
					Player[playerid][pArmour]);
		}
		case 1:
		{
			if (!Player[playerid][Playing])
				format(iString, sizeof(iString), "{FFFFFF}%s {CCCCCC}has quit the server.", Player[playerid][Name]);
			else
				format(
					iString, sizeof(iString), "{FFFFFF}%s {CCCCCC}has quit the server {FFFFFF}(HP %d | AP %d).", Player[playerid][Name], Player[playerid][pHealth],
					Player[playerid][pArmour]);
		}
		case 2:
		{
			if (!Player[playerid][Playing])
				format(iString, sizeof(iString), "{FFFFFF}%s {CCCCCC}has been kicked or banned.", Player[playerid][Name]);
			else
				format(
					iString, sizeof(iString), "{FFFFFF}%s {CCCCCC}has been kicked or banned {FFFFFF}(HP %d | AP %d).", Player[playerid][Name], Player[playerid][pHealth],
					Player[playerid][pArmour]);
		}
	}
	SendClientMessageToAll(-1, iString);
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
