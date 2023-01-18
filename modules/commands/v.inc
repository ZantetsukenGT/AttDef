#if defined _attdef_cmd_v
	#endinput
#endif
#define _attdef_cmd_v

YCMD: v(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "spawn a vehicle.");
	if (Player[playerid][Spectating])
		return SendErrorMessage(playerid, "Can't use this command while spectating.");
	if (Player[playerid][InDM])
		return SendErrorMessage(playerid, "You can't spawn vehicle in DM.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (RoundPaused && Player[playerid][Playing])
		return 1;
	if (Player[playerid][Playing] && Player[playerid][TimesSpawned] > 5)
		return SendErrorMessage(playerid, "You have spawned the maximum number of vehicles (5).");
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "Can't spawn a vehicle while you are not the driver.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/v [Vehicle Name/ID]");

	new veh = IsNumeric(params) ? strval(params) : GetVehicleModelID(params);
	if (veh < 400 || veh > 611)
		return SendErrorMessage(playerid, "Invalid Vehicle Name."); //In samp there is no vehile with ID below 400 or above 611

	//Block some vehiles that u don't like e.g. Tank, hunter. It wil be annoying in lobby. To search for more vehicle IDs try samp wiki.
	if (veh == 407 || veh == 425 || veh == 430 || veh == 432 || veh == 435 || veh == 441 || veh == 447 || veh == 449
		|| veh == 450 || veh == 464 || veh == 465 || veh == 476 || veh == 501 || veh == 512 || veh == 520 || veh == 537
		|| veh == 538 || veh == 564 || veh == 569 || veh == 570 || veh == 577 || veh == 584 || veh == 590 || veh == 591
		|| veh == 592 || veh == 594 || veh == 601 || veh == 606 || veh == 607 || veh == 608 || veh == 610 || veh == 611)
		return SendErrorMessage(playerid, "This vehicle is blocked.");

	new Float: x,
		Float: y,
		Float: z,
		Float: r;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, r);

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

	if (Player[playerid][Playing])
	{
		if (Player[playerid][Team] != ATTACKER)
			return SendErrorMessage(playerid, "Only attackers can spawn vehicle.");
		if (GameType != BASE)
			return SendErrorMessage(playerid, "Vehicles can only be spawned in bases.");
		if (BInterior[Current] != 0)
			return SendErrorMessage(playerid, "You can't spawn vehicle in interior base.");
		if (!IsPlayerInRangeOfPoint(playerid, 100.0, BAttackerSpawn[Current][0], BAttackerSpawn[Current][1], BAttackerSpawn[Current][2]))
			return SendErrorMessage(playerid, "You are too far from attacker spawn."); //If attacker is too far away from his spawn.
	}

	new vehicleid = FreezeV_CreateVehicle(Player[playerid][Playing], veh, x, y, z, r, -1, -1, -1); //Creates the specific vehicle u were looking for (veh).
	if (vehicleid == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "Server's vehicle limit was reached and cannot spawn any more.");

	SetVehicleNumberPlate(vehicleid, Player[playerid][NameWithoutTag]);
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));		//Links vehicle interior to the current player interior.
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid)); //Sets vehicle virtual world the the current virtual world of the player.
	PutPlayerInVehicle(playerid, vehicleid, 0);							//Puts player in the driver seat.

	if (Player[playerid][Playing])
		Player[playerid][TimesSpawned]++;
	else
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

	if (Player[playerid][Playing])
	{
		new iString[144];
		format(
			iString, sizeof(iString), "%s%s{FFFFFF} has spawned a(n) %s%s", TextColor[Player[playerid][Team]], Player[playerid][Name], TextColor[Player[playerid][Team]],
			aVehicleNames[veh - 400]);

		foreach (new i : Player)
		{
			if (IsTeamTheSame(Player[i][Team], Player[playerid][Team]))
				SendClientMessage(i, -1, iString);
		}
	}
	return 1;
}
