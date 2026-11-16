#if defined _attdef_cmd_acar
	#endinput
#endif
#define _attdef_cmd_acar

YCMD: acar(playerid, params[], help)
{
	////if(Player[playerid][Level] < 4 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher level admin to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "spawn a car as an administrator (including blocked vehicles).");
	if (Player[playerid][Spectating])
		return SendErrorMessage(playerid, "Can't use this command while spectating.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command in rounds.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "Can't spawn a vehicle while you are not the driver.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/acar [Vehicle Name/ID]");

	new veh = IsNumeric(params) ? strval(params) : GetVehicleModelID(params);
	if (veh < 400 || veh > 611)
		return SendErrorMessage(playerid, "Invalid Vehicle Name/ID."); //In samp there is no vehile with ID below 400 or above 611

	new pLastVehicle = Player[playerid][LastVehicle];
	if (pLastVehicle)
	{
		foreach (new i : VehicleDriver(pLastVehicle))
		{
			RemovePlayerFromVehicle(i);
		}
		foreach (new i : VehiclePassenger(pLastVehicle))
		{
			RemovePlayerFromVehicle(i);
		}
		DestroyVehicle(pLastVehicle);
		Player[playerid][LastVehicle] = 0;
	}

	new Float: x,
		Float: y,
		Float: z,
		Float: r;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, r);

	new vehicleid = FreezeV_CreateVehicle(Player[playerid][Playing], veh, x, y, z, r, -1, -1, -1); //Creates the specific vehicle u were looking for (veh).
	if (vehicleid == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "Server's vehicle limit was reached and cannot spawn any more.");

	SetVehicleNumberPlate(vehicleid, Player[playerid][NameWithoutTag]);
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));		//Links vehicle interior to the current player interior.
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid)); //Sets vehicle virtual world the the current virtual world of the player.
	PutPlayerInVehicle(playerid, vehicleid, 0);							//Puts player in the driver seat.

	Player[playerid][LastVehicle] = vehicleid;

	switch (veh)
	{
		case 560: // Sultan mods (most spawned car)
		{
			for (new i = 1026; i <= 1033; i++) { AddVehicleComponent(vehicleid, i); }
			AddVehicleComponent(vehicleid, 1138);
			AddVehicleComponent(vehicleid, 1141);
		}
		case 565: // Flash mods
		{
			for (new i = 1045; i <= 1054; i++) { AddVehicleComponent(vehicleid, i); }
		}
		case 535: // Slamvan
		{
			for (new i = 1110; i <= 1122; i++) { AddVehicleComponent(vehicleid, i); }
		}
	}
	AddVehicleComponent(vehicleid, 1025); // Offroad wheels
	AddVehicleComponent(vehicleid, 1087); // Hydraulics

	LogAdminCommand("acar", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s%s{FFFFFF} has spawned a(n) %s%s {FFFFFF}as admin", TextColor[Player[playerid][Team]], Player[playerid][Name],
		TextColor[Player[playerid][Team]], aVehicleNames[veh - 400]);
}
