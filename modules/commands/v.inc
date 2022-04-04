#if defined _attdef_cmd_v
	#endinput
#endif
#define _attdef_cmd_v

YCMD: v(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "spawn a vehicle.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/v [Vehicle name or ID]");
	if (Player[playerid][Spectating])
		return 1;
	if (RoundPaused && Player[playerid][Playing])
		return 1;
	if (Player[playerid][InDM])
		return SendErrorMessage(playerid, "You can't spawn vehicle in DM.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (Player[playerid][Playing] && Player[playerid][TimesSpawned] >= 2)
		return SendErrorMessage(playerid, "You have spawned the maximum number of vehicles.");
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "Can't spawn a vehicle while you are not the driver.");

	new veh = IsNumeric(params) ? strval(params) : GetVehicleModelID(params);
	if (veh < 400 || veh > 611)
		return SendErrorMessage(playerid, "Invalid Vehicle Name."); //In samp there is no vehile with ID below 400 or above 611

	//Block some vehiles that u don't like e.g. Tank, hunter. It wil be annoying in lobby. To search for more vehicle IDs try samp wiki.
	if (veh == 407 || veh == 425 || veh == 430 || veh == 432 || veh == 435 || veh == 441 || veh == 447 || veh == 449)
		return SendErrorMessage(playerid, "This vehicle is blocked.");
	if (veh == 450 || veh == 464 || veh == 465 || veh == 476 || veh == 501 || veh == 512 || veh == 520 || veh == 537)
		return SendErrorMessage(playerid, "This vehicle is blocked.");
	if (veh == 538 || veh == 564 || veh == 569 || veh == 570 || veh == 577 || veh == 584 || veh == 590 || veh == 591)
		return SendErrorMessage(playerid, "This vehicle is blocked.");
	if (veh == 592 || veh == 594 || veh == 601 || veh == 606 || veh == 607 || veh == 608 || veh == 610 || veh == 611)
		return SendErrorMessage(playerid, "This vehicle is blocked.");

	//	Allowed vehicles:	472=Coastguard	544=Firetruck LA	553=Nevada	595=Launch

	new Float: Pos[4];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	GetPlayerFacingAngle(playerid, Pos[3]);

	if (Player[playerid][Playing])
	{
		if (Player[playerid][Team] == DEFENDER || Player[playerid][Team] == REFEREE)
			return SendErrorMessage(playerid, "Only attackers can spawn vehicle.");
		if (BInterior[Current] != 0)
			return SendErrorMessage(playerid, "You can't spawn vehicle in interior base.");

		if (Player[playerid][Team] == ATTACKER
			&& (Pos[0] > BAttackerSpawn[Current][0] + 100 || Pos[0] < BAttackerSpawn[Current][0] - 100 || Pos[1] > BAttackerSpawn[Current][1] + 100
				|| Pos[1] < BAttackerSpawn[Current][1] - 100))
			return SendErrorMessage(playerid, "You are too far from attacker spawn."); //If attacker is too far away from his spawn.
	}

	if (IsPlayerInAnyVehicle(playerid))
	{
		Player[playerid][LastVehicle] = -1;
		RemoveVehicle(GetPlayerVehicleID(playerid)); //If you are already in a vehicle and use /car, it will destroy that vehicle first and spawn the new one.
	}

	if (!Player[playerid][Playing])
	{
		if (Player[playerid][LastVehicle] != -1)
		{
			new bool: InVehicle = false;
			foreach (new i : Player)
			{
				if (i != playerid && IsPlayerInVehicle(i, Player[playerid][LastVehicle]))
					InVehicle = true;
			}

			if (!InVehicle)
				RemoveVehicle(Player[playerid][LastVehicle]);

			Player[playerid][LastVehicle] = -1;
		}
	}
	new MyVehicle = CreateVehicle(veh, Pos[0], Pos[1], Pos[2], Pos[3], -1, -1, -1); //Creates the specific vehicle u were looking for (veh).
	new plate[MAX_PLAYER_NAME];
	format(plate, sizeof(plate), "%s", Player[playerid][NameWithoutTag]);
	SetVehicleNumberPlate(MyVehicle, plate);
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

	if (Player[playerid][Playing])
	{
		new iString[128];
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
