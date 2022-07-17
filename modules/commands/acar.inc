#if defined _attdef_cmd_acar
	#endinput
#endif
#define _attdef_cmd_acar

YCMD: acar(playerid, params[], help)
{
	////if(Player[playerid][Level] < 4 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher level admin to do that.");
	if (help)
		return SendCommandHelpMessage(playerid, "spawn a car as an administrator (including blocked vehicles).");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command in rounds");
	if (isnull(params))
		return SendUsageMessage(playerid, "/acar [Vehicle Name]");
	if (Player[playerid][Spectating])
		return 1;
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (Player[playerid][Playing] && Player[playerid][TimesSpawned] >= 3)
		return SendErrorMessage(playerid, "You have spawned the maximum number of vehicles.");
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "Can't spawn a vehicle while you are not the driver.");

	new veh = IsNumeric(params) ? strval(params) : GetVehicleModelID(params);

	if (veh < 400 || veh > 611)
		return SendErrorMessage(playerid, "Invalid Vehicle Name."); //In samp there is no vehile with ID below 400 or above 611

	if (!Player[playerid][Playing])
	{
		if (IsPlayerInAnyVehicle(playerid))
		{
			RemovePlayerFromVehicle(playerid);
			RemoveVehicle(GetPlayerVehicleID(playerid));
			Player[playerid][LastVehicle] = -1;
		}

		if (Player[playerid][LastVehicle] != -1)
		{
			RemoveVehicle(Player[playerid][LastVehicle]);
			Player[playerid][LastVehicle] = -1;
		}
	}

	new Float: Pos[4];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	GetPlayerFacingAngle(playerid, Pos[3]);

	if (IsPlayerInAnyVehicle(playerid))
	{
		RemoveVehicle(GetPlayerVehicleID(playerid)); //If you are already in a vehicle and use /car, it will destroy that vehicle first and spawn the new one.
	}

	new MyVehicle = CreateVehicle(veh, Pos[0], Pos[1], Pos[2], Pos[3], -1, -1, -1); //Creates the specific vehicle u were looking for (veh).

	new plate[MAX_PLAYER_NAME];
	format(plate, sizeof(plate), "%s", Player[playerid][NameWithoutTag]);
	SetVehicleNumberPlate(MyVehicle, plate);
	SetVehicleToRespawn(MyVehicle);

	LinkVehicleToInterior(MyVehicle, GetPlayerInterior(playerid));		//Links vehicle interior to the current player interior.
	SetVehicleVirtualWorld(MyVehicle, GetPlayerVirtualWorld(playerid)); //Sets vehicle virtual world the the current virtual world of the player.
	PutPlayerInVehicle(playerid, MyVehicle, 0);							//Puts player in the driver seat.

	if (!Player[playerid][Playing])
		Player[playerid][LastVehicle] = GetPlayerVehicleID(playerid);
	else
		Player[playerid][TimesSpawned]++;

	switch (veh)
	{
		case 560: // Sultan mods (most spawned car)
		{
			for (new i = 1026; i <= 1033; i++) { AddVehicleComponent(MyVehicle, i); }
			AddVehicleComponent(MyVehicle, 1138);
			AddVehicleComponent(MyVehicle, 1141);
		}
		case 565: // Flash mods
		{
			for (new i = 1045; i <= 1054; i++) { AddVehicleComponent(MyVehicle, i); }
		}
		case 535: // Slamvan
		{
			for (new i = 1110; i <= 1122; i++) { AddVehicleComponent(MyVehicle, i); }
		}
	}
	AddVehicleComponent(MyVehicle, 1025); // Offroad wheels
	AddVehicleComponent(MyVehicle, 1087); // Hydraulics

	LogAdminCommand("acar", playerid, INVALID_PLAYER_ID);

	return va_SendClientMessageToAll(-1, "%s%s{FFFFFF} has spawned a(n) %s%s {FFFFFF}as admin", TextColor[Player[playerid][Team]], Player[playerid][Name],
		TextColor[Player[playerid][Team]], aVehicleNames[veh - 400]);
}
