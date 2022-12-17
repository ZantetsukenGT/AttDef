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

	new veh = IsNumeric(params) ? max(strval(params), 0) : GetVehicleModelID(params);
	if (veh > GetNumVehicleModels())
		return SendErrorMessage(playerid, "Invalid Vehicle Name.");
	new modelid = GetValidVehicleModelAt(veh);
	if (modelid == -1)
		return SendErrorMessage(playerid, "Invalid Vehicle Name."); //In samp there is no vehile with ID below 400 or above 611

	//Block some vehiles that u don't like e.g. Tank, hunter. It wil be annoying in lobby. To search for more vehicle IDs try samp wiki.
	if (modelid == 407 || modelid == 425 || modelid == 430 || modelid == 432 || modelid == 435 || modelid == 441 || modelid == 447 || modelid == 449
		|| modelid == 450 || modelid == 464 || modelid == 465 || modelid == 476 || modelid == 501 || modelid == 512 || modelid == 520 || modelid == 537
		|| modelid == 538 || modelid == 564 || modelid == 569 || modelid == 570 || modelid == 577 || modelid == 584 || modelid == 590 || modelid == 591
		|| modelid == 592 || modelid == 594 || modelid == 601 || modelid == 606 || modelid == 607 || modelid == 608 || modelid == 610 || modelid == 611)
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
		foreach (new i : VehicleOccupant(pLastVehicle))
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

		new vehicleid = GetPlayerVehicleID(playerid);
		if (vehicleid)
		{
			foreach (new i : VehicleOccupant(vehicleid))
			{
				RemovePlayerFromVehicle(i);
			}
			DestroyVehicle(vehicleid);
		}
	}

	new vehicleid = CreateVehicle(modelid, x, y, z, r, -1, -1, -1); //Creates the specific vehicle u were looking for (veh).
	if (vehicleid == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "Server's vehicle limit was reached and cannot spawn any more.");

	if (Iter_Contains(GMFrozenCars, vehicleid))
	{
		KillTimer(GMFrozenCarTimers[vehicleid]);
		Iter_Remove(GMFrozenCars, vehicleid);
	}
	if (Iter_Contains(FrozenCars, vehicleid))
	{
		KillTimer(FrozenCarTimers[vehicleid]);
		Iter_Remove(FrozenCars, vehicleid);
	}

	SetVehicleNumberPlate(vehicleid, Player[playerid][NameWithoutTag]);
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));		//Links vehicle interior to the current player interior.
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid)); //Sets vehicle virtual world the the current virtual world of the player.
	PutPlayerInVehicle(playerid, vehicleid, 0);							//Puts player in the driver seat.

	if (Player[playerid][Playing])
		Player[playerid][TimesSpawned]++;
	else
		Player[playerid][LastVehicle] = vehicleid;

	switch (modelid)
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
			aVehicleNames[veh]);

		foreach (new i : Player)
		{
			if (IsTeamTheSame(Player[i][Team], Player[playerid][Team]))
				SendClientMessage(i, -1, iString);
		}
	}
	return 1;
}
