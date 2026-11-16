#if defined _attdef_OnPKeyStateChange
	#endinput
#endif
#define _attdef_OnPKeyStateChange

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new currentTick = GetTickCount();
	new vehicleid = GetPlayerVehicleID(playerid);
	// - High priority key functions
	if (PRESSED(KEY_JUMP | KEY_HANDBRAKE) && !vehicleid)
	{
		switch (GetWeaponSlot(GetPlayerWeapon(playerid)))
		{
			case 0, 1, 8, 11:
			{
				SyncPlayer(playerid);
				return 1;
			}
		}
	}
	if (AntiMacros && CheckPlayerSprintMacro(playerid, newkeys, oldkeys))
		return 1;

	if (PRESSED(KEY_FIRE)) // key fire
	{
		if (Player[playerid][TextDrawOnScreen] && (LastMatchEndTime + 2) - gettime() <= 0)
		{
			HideEndRoundTextDraw(playerid);
			return 1;
		}
		if (Player[playerid][InDeathCamera])
		{
			OnPlayerDeathCameraEnd(playerid);
			return 1;
		}
	}
	if (Player[playerid][Spectating] && !noclipdata[playerid][FlyMode] && Player[playerid][SpectatingRound] == -1)
	{
		if (PRESSED(KEY_FIRE))
		{
			if (Current != -1)
				SpectateNextTeamPlayer(playerid);
			else
				SpectateNextPlayer(playerid);
		}
		else if (PRESSED(KEY_HANDBRAKE))
		{
			if (Current != -1)
				SpectatePreviousTeamPlayer(playerid);
			else
				SpectatePreviousPlayer(playerid);
		}
		return 1;
	}
	if (Current != -1)
	{
		if (Player[playerid][Playing])
		{
			if (PRESSED(KEY_NO) && AllowStartBase)
			{
				if (PlayerRequestBackup(playerid))
					return 1;
			}
			// Lead team
			if (PRESSED(KEY_CTRL_BACK) && AllowStartBase)
			{
				if (vehicleid)
					return 1;

				if (currentTick - Player[playerid][LastAskLeader] < 5000)
				{
					SendErrorMessage(playerid, "Please wait.");
					return 0;
				}
				new team = Player[playerid][Team];
				if (TeamHasLeader[team] != true)
				{
					PlayerLeadTeam(playerid, false, true);
				}
				else
				{
					if (TeamLeader[team] == playerid) // off
					{
						PlayerNoLeadTeam(playerid);
					}
					else
						SendErrorMessage(playerid, "Your team already has a leader!");
				}
				Player[playerid][LastAskLeader] = currentTick;
				return 1;
			}
		}

		// Pause/unpause or ask for pause/unpause
		if (PRESSED(KEY_YES))
		{
			if (Player[playerid][Level] > 0)
			{
				if (!Player[playerid][Spectating] && Player[playerid][Playing] == false)
					return 1;

				switch (RoundPaused)
				{
					case true:
					{
						new iString[144];
						if (currentTick - PausePressed < 3000)
							return SendErrorMessage(playerid, "Please Wait.");
						if (RoundUnpausing == true)
							return 1;

						PauseCountdown = 4;
						UnpauseRound();

						format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has unpaused the current round.", Player[playerid][Name]);
						SendClientMessageToAll(-1, iString);
						return 1;
					}
					case false:
					{
						new iString[144];
						if (RoundUnpausing == true)
							return SendErrorMessage(playerid, "Round is unpausing, please wait.");

						PausePressed = currentTick;

						PauseRound();

						format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has paused the current round.", Player[playerid][Name]);
						SendClientMessageToAll(-1, iString);
						return 1;
					}
				}
			}
			else
			{
				if (!Player[playerid][Playing])
					return 1;

				if (currentTick - Player[playerid][lastChat] < 7500)
				{
					SendErrorMessage(playerid, "Please wait.");
					return 0;
				}
				foreach (new i : Player)
					PlayerPlaySound(i, 1133, 0.0, 0.0, 0.0);
				Player[playerid][lastChat] = currentTick;
				SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "is asking for an %spause!", Player[playerid][Name], RoundPaused ? "un" : ""));
				return 1;
			}
		}
	}

	// - Low priority key functions

	if (CheckKeysForWeaponBind(playerid, newkeys, oldkeys))
		return 1;

	if (vehicleid && PRESSED(KEY_FIRE) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		AddVehicleComponent(vehicleid, 1010);
		return 1;
	}

	if (Player[playerid][SpectatingRound] != -1)
	{
		switch (Player[playerid][SpectatingType])
		{
			case BASE:
			{
				if (Iter_Count(CurrentBases) > 1)
				{
					if (PRESSED(KEY_FIRE))
					{
						new i = Player[playerid][SpectatingRound];
						if (i == Iter_First(CurrentBases))
							Player[playerid][SpectatingRound] = Iter_Last(CurrentBases);
						else
							Player[playerid][SpectatingRound] = Iter_Prev(CurrentBases, i);
						i = Player[playerid][SpectatingRound];
						SetPlayerInterior(playerid, BInterior[i]);
						SetPlayerCameraLookAt(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);
						SetPlayerCameraPos(playerid, BCPSpawn[i][0] + 100, BCPSpawn[i][1], BCPSpawn[i][2] + 80);
						SetPlayerPos(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);

						va_PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "%sBase ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, BName[i], i, MAIN_TEXT_COLOUR);
					}
					else if (PRESSED(KEY_HANDBRAKE))
					{
						new i = Player[playerid][SpectatingRound];
						if (i == Iter_Last(CurrentBases))
							Player[playerid][SpectatingRound] = Iter_First(CurrentBases);
						else
							Player[playerid][SpectatingRound] = Iter_Next(CurrentBases, i);
						i = Player[playerid][SpectatingRound];
						SetPlayerInterior(playerid, BInterior[i]);
						SetPlayerCameraLookAt(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);
						SetPlayerCameraPos(playerid, BCPSpawn[i][0] + 100, BCPSpawn[i][1], BCPSpawn[i][2] + 80);
						SetPlayerPos(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);

						va_PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "%sBase ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, BName[i], i, MAIN_TEXT_COLOUR);
					}
				}
			}
			case ARENA:
			{
				if (Iter_Count(CurrentArenas) > 1)
				{
					if (PRESSED(KEY_FIRE))
					{
						new i = Player[playerid][SpectatingRound];
						if (i == Iter_First(CurrentArenas))
							Player[playerid][SpectatingRound] = Iter_Last(CurrentArenas);
						else
							Player[playerid][SpectatingRound] = Iter_Prev(CurrentArenas, i);
						i = Player[playerid][SpectatingRound];
						SetPlayerCameraLookAt(playerid, ACPSpawn[i][0], ACPSpawn[i][1], ACPSpawn[i][2]);
						SetPlayerCameraPos(playerid, ACPSpawn[i][0] + 100, ACPSpawn[i][1], ACPSpawn[i][2] + 80);
						SetPlayerPos(playerid, ACPSpawn[i][0], ACPSpawn[i][1], ACPSpawn[i][2]);
						SetPlayerInterior(playerid, AInterior[i]);

						va_PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "%sArena ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, AName[i], i, MAIN_TEXT_COLOUR);
					}
					else if (PRESSED(KEY_HANDBRAKE))
					{
						new i = Player[playerid][SpectatingRound];
						if (i == Iter_Last(CurrentArenas))
							Player[playerid][SpectatingRound] = Iter_First(CurrentArenas);
						else
							Player[playerid][SpectatingRound] = Iter_Next(CurrentArenas, i);
						i = Player[playerid][SpectatingRound];
						SetPlayerCameraLookAt(playerid, ACPSpawn[i][0], ACPSpawn[i][1], ACPSpawn[i][2]);
						SetPlayerCameraPos(playerid, ACPSpawn[i][0] + 100, ACPSpawn[i][1], ACPSpawn[i][2] + 80);
						SetPlayerPos(playerid, ACPSpawn[i][0], ACPSpawn[i][1], ACPSpawn[i][2]);
						SetPlayerInterior(playerid, AInterior[i]);

						va_PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "%sArena ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, AName[i], i, MAIN_TEXT_COLOUR);
					}
				}
			}
		}
		if (PRESSED(KEY_JUMP))
		{
			switch (Player[playerid][SpectatingType])
			{
				case BASE:
					va_SendClientMessage(
						playerid, -1, COL_PRIM "Spectating Base: {FFFFFF}%s (ID: %d)", BName[Player[playerid][SpectatingRound]], Player[playerid][SpectatingRound]);
				case ARENA:
					va_SendClientMessage(
						playerid, -1, COL_PRIM "Spectating Arena: {FFFFFF}%s (ID: %d)", AName[Player[playerid][SpectatingRound]], Player[playerid][SpectatingRound]);
			}
			SetCameraBehindPlayer(playerid);
			Player[playerid][SpectatingRound] = -1;
			PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "_");
			Player[playerid][Spectating] = false;
		}
		return 1;
	}
	if (Current == -1)
	{
		if (PRESSED(KEY_YES) && Player[playerid][Level] > 1 && !vehicleid)
		{
			EnableMatchInterface(playerid);
			return 1;
		}
	}
	if (PRESSED(KEY_NO) && !Player[playerid][Playing])
	{
		ShowEndRoundTextDraw(playerid);
		return 1;
	}
	return 1;
}
