#if defined _attdef_cmd_int
	#endinput
#endif
#define _attdef_cmd_int

YCMD: int(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "teleport you to an interior.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, COL_PRIM "Can't use while round is active.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	new id;
	if (sscanf(params, "i", id) || id <= 0 || id > 147)
		return SendUsageMessage(playerid, COL_PRIM "/int [1-147]");

	if (Player[playerid][Spectating])
		StopSpectate(playerid);
	if (Player[playerid][InDM])
		QuitDM(playerid);
	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	if (IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		foreach (new i : Player)
		{
			if (vehicleid == GetPlayerVehicleID(i))
				SetPlayerInterior(i, Interiors[id][int_interior]);
		}
		SetVehiclePos(GetPlayerVehicleID(playerid), Interiors[id][int_x], Interiors[id][int_y], Interiors[id][int_z]);
		SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
		LinkVehicleToInterior(GetPlayerVehicleID(playerid), Interiors[id][int_interior]);
		SetCameraBehindPlayer(playerid);
	}
	else
	{
		SetPlayerPos(playerid, Interiors[id][int_x], Interiors[id][int_y], Interiors[id][int_z]);
		SetPlayerFacingAngle(playerid, Interiors[id][int_a]);
		SetPlayerInterior(playerid, Interiors[id][int_interior]);
		SetCameraBehindPlayer(playerid);
	}

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has entered Interior ID: {FFFFFF}%d", Player[playerid][Name], id);
}
