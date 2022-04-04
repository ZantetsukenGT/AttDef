#if defined _attdef_OnPKeyStateChange
	#endinput
#endif
#define _attdef_OnPKeyStateChange

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new currentTick = GetTickCount();
	// - High priority key functions
	if (PRESSED(KEY_JUMP | KEY_HANDBRAKE) && GetPlayerVehicleID(playerid) == 0)
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
				if (GetPlayerVehicleID(playerid))
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
						if ((GetTickCount() - PausePressed) < 3000)
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

						PausePressed = GetTickCount();

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

	if (GetPlayerVehicleID(playerid) && PRESSED(KEY_FIRE) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
		return 1;
	}

	if (Player[playerid][SpectatingRound] != -1)
	{
		new iString[128];
		switch (Player[playerid][SpectatingType])
		{
			case BASE:
			{
				if (PRESSED(KEY_FIRE))
				{
					new searching;
					for (new i = Player[playerid][SpectatingRound] + 1; i <= MAX_BASES; i++)
					{
						if (searching > 1)
						{
							break;
						}
						if (i == MAX_BASES)
						{
							i = 1;
							searching++;
						}
						if (BExist[i] == true)
						{
							Player[playerid][SpectatingRound] = i;
							SetPlayerInterior(playerid, BInterior[i]);
							SetPlayerCameraLookAt(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);
							SetPlayerCameraPos(playerid, BCPSpawn[i][0] + 100, BCPSpawn[i][1], BCPSpawn[i][2] + 80);
							SetPlayerPos(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);
							format(iString, sizeof(iString), "%sBase ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, BName[i], i, MAIN_TEXT_COLOUR);
							PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], iString);
							break;
						}
					}
				}
				else if (PRESSED(KEY_HANDBRAKE))
				{
					new searching;
					for (new i = Player[playerid][SpectatingRound] - 1; i >= 0; i--)
					{
						if (searching > 1)
						{
							break;
						}
						if (i == 0)
						{
							i = MAX_BASES - 1;
							searching++;
						}

						if (BExist[i] == true)
						{
							Player[playerid][SpectatingRound] = i;
							SetPlayerInterior(playerid, BInterior[i]);
							SetPlayerCameraLookAt(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);
							SetPlayerCameraPos(playerid, BCPSpawn[i][0] + 100, BCPSpawn[i][1], BCPSpawn[i][2] + 80);
							SetPlayerPos(playerid, BCPSpawn[i][0], BCPSpawn[i][1], BCPSpawn[i][2]);

							format(iString, sizeof(iString), "%sBase ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, BName[i], i, MAIN_TEXT_COLOUR);
							PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], iString);
							break;
						}
					}
				}
			}
			case ARENA:
			{
				if (PRESSED(KEY_FIRE))
				{
					new searching;
					for (new i = Player[playerid][SpectatingRound] + 1; i <= MAX_ARENAS; i++)
					{
						if (searching > 1)
						{
							break;
						}
						if (i == MAX_ARENAS)
						{
							i = 0;
							searching++;
						}
						if (AExist[i] == true)
						{
							Player[playerid][SpectatingRound] = i;
							SetPlayerCameraLookAt(
								playerid, ACPSpawn[Player[playerid][SpectatingRound]][0], ACPSpawn[Player[playerid][SpectatingRound]][1],
								ACPSpawn[Player[playerid][SpectatingRound]][2]);
							SetPlayerCameraPos(
								playerid, ACPSpawn[Player[playerid][SpectatingRound]][0] + 100, ACPSpawn[Player[playerid][SpectatingRound]][1],
								ACPSpawn[Player[playerid][SpectatingRound]][2] + 80);
							SetPlayerPos(
								playerid, ACPSpawn[Player[playerid][SpectatingRound]][0], ACPSpawn[Player[playerid][SpectatingRound]][1],
								ACPSpawn[Player[playerid][SpectatingRound]][2]);
							SetPlayerInterior(playerid, AInterior[Player[playerid][SpectatingRound]]);

							format(
								iString, sizeof(iString), "%sArena ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, AName[Player[playerid][SpectatingRound]],
								Player[playerid][SpectatingRound], MAIN_TEXT_COLOUR);
							PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], iString);
							break;
						}
					}
				}
				else if (PRESSED(KEY_HANDBRAKE))
				{
					new searching;
					for (new i = Player[playerid][SpectatingRound] - 1; i >= 0; i--)
					{
						if (searching > 1)
						{
							break;
						}
						if (i == 0)
						{
							i = MAX_ARENAS - 1;
							searching++;
						}

						if (AExist[i] == true)
						{
							Player[playerid][SpectatingRound] = i;
							SetPlayerCameraLookAt(
								playerid, ACPSpawn[Player[playerid][SpectatingRound]][0], ACPSpawn[Player[playerid][SpectatingRound]][1],
								ACPSpawn[Player[playerid][SpectatingRound]][2]);
							SetPlayerCameraPos(
								playerid, ACPSpawn[Player[playerid][SpectatingRound]][0] + 100, ACPSpawn[Player[playerid][SpectatingRound]][1],
								ACPSpawn[Player[playerid][SpectatingRound]][2] + 80);
							SetPlayerPos(
								playerid, ACPSpawn[Player[playerid][SpectatingRound]][0], ACPSpawn[Player[playerid][SpectatingRound]][1],
								ACPSpawn[Player[playerid][SpectatingRound]][2]);
							SetPlayerInterior(playerid, AInterior[Player[playerid][SpectatingRound]]);

							format(
								iString, sizeof(iString), "%sArena ~n~%s%s (ID: ~r~%d%s)", MAIN_TEXT_COLOUR, MAIN_TEXT_COLOUR, AName[Player[playerid][SpectatingRound]],
								Player[playerid][SpectatingRound], MAIN_TEXT_COLOUR);
							PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], iString);
							break;
						}
					}
				}
			}
		}
		if (PRESSED(KEY_JUMP))
		{
			switch (Player[playerid][SpectatingType])
			{
				case BASE:
					format(
						iString, sizeof(iString), "" COL_PRIM "Spectating Base: {FFFFFF}%s (ID: %d)", BName[Player[playerid][SpectatingRound]], Player[playerid][SpectatingRound]);
				case ARENA:
					format(
						iString, sizeof(iString), "" COL_PRIM "Spectating Arena: {FFFFFF}%s (ID: %d)", AName[Player[playerid][SpectatingRound]], Player[playerid][SpectatingRound]);
			}
			SendClientMessage(playerid, -1, iString);
			SetCameraBehindPlayer(playerid);
			Player[playerid][SpectatingRound] = -1;
			PlayerTextDrawSetString(playerid, TD_RoundSpec[playerid], "_");
			Player[playerid][Spectating] = false;
		}
		return 1;
	}
	if (Current == -1)
	{
		if (PRESSED(KEY_YES) && Player[playerid][Level] > 1 && GetPlayerVehicleID(playerid) == 0)
		{
			EnableMatchInterface(playerid);
			return 1;
		}
		else if (PRESSED(KEY_NO) && GetPlayerVehicleID(playerid) == 0)
		{
			ShowEndRoundTextDraw(playerid);
			return 1;
		}
	}
	return 1;
}
