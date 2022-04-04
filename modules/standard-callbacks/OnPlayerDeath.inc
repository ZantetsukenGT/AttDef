#if defined _attdef_OnPDeath
	#endinput
#endif
#define _attdef_OnPDeath



forward ServerOnPlayerDeath(playerid, killerid, reason);
public ServerOnPlayerDeath(playerid, killerid, reason)
{
	Player[playerid][AlreadyDying] = false; // Player is no longer dying, server-sided death is taking place
	Player[playerid][HitBy]		   = INVALID_PLAYER_ID;
	Player[playerid][HitWith]	   = 47;

	new KillerConnected			   = IsPlayerConnected(killerid);
	if (!KillerConnected)
	{
		if (Player[playerid][Playing] == true)
		{
			SendDeathMessage(INVALID_PLAYER_ID, playerid, reason);
			Player[playerid][RoundDeaths]++;
			Player[playerid][TotalDeaths]++;

			SendClientMessageToAll(-1, va_return("%s%s {FFFFFF}has died by: {FFFFFF}%s", TextColor[Player[playerid][Team]], Player[playerid][Name], WeaponNames[reason]));
			MessageBox(playerid, MSGBOX_TYPE_TOP, "wasted", "_", 3000, false);
			OnPlayerAmmoUpdate(playerid);
		}
		else if (Current == -1)
			SendDeathMessage(INVALID_PLAYER_ID, playerid, reason);
	}
	else
	{
		if (!RandomDeathMessages)
		{
			PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("%sKilled By: ~r~%s", MAIN_TEXT_COLOUR, Player[killerid][Name]));
			PlayerTextDrawSetString(killerid, DeathText[killerid][0], va_return("%sYou Killed: ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]));
		}
		else
		{
			switch (reason)
			{
				case WEAPON_KNIFE:
				{
					PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("~rp~%s%s knifed you", Player[killerid][Name], MAIN_TEXT_COLOUR));
					PlayerTextDrawSetString(killerid, DeathText[killerid][0], va_return("%sYou knifed ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]));
				}
				case WEAPON_GRENADE:
				{
					PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("~r~%s%s bombed you", Player[killerid][Name], MAIN_TEXT_COLOUR));
					PlayerTextDrawSetString(killerid, DeathText[killerid][0], va_return("%sYou bombed ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]));
				}
				default:
				{
					switch (random(4))
					{
						case 0:
						{
							PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("~r~%s%s raped you", Player[killerid][Name], MAIN_TEXT_COLOUR));
							PlayerTextDrawSetString(killerid, DeathText[killerid][0], va_return("%sYou raped ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]));
						}
						case 1:
						{
							PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("~r~%s%s owned you", Player[killerid][Name], MAIN_TEXT_COLOUR));
							PlayerTextDrawSetString(killerid, DeathText[killerid][0], va_return("%sYou owned ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]));
						}
						case 2:
						{
							PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("~r~%s%s murdered you", Player[killerid][Name], MAIN_TEXT_COLOUR));
							PlayerTextDrawSetString(killerid, DeathText[killerid][0], va_return("%sYou murdered ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]));
						}
						case 3:
						{
							PlayerTextDrawSetString(playerid, DeathText[playerid][1], va_return("~r~%s%s sent you to cemetery", Player[killerid][Name], MAIN_TEXT_COLOUR));
							PlayerTextDrawSetString(
								killerid, DeathText[killerid][0], va_return("%sYou sent ~r~%s%s to cemetery", MAIN_TEXT_COLOUR, Player[playerid][Name], MAIN_TEXT_COLOUR));
						}
					}
				}
			}
		}

		PlayerTextDrawShow(killerid, DeathText[killerid][0]);
		PlayerTextDrawShow(playerid, DeathText[playerid][1]);

		SetPreciseTimer("DeathMessageF", 4000, false, "ii", killerid, playerid);

		if (Player[playerid][Playing] && Player[killerid][Playing] && AllowStartBase)
		{
			ShowPlayerDeathMessage(killerid, playerid);
			SendDeathMessage(killerid, playerid, reason);

			Player[killerid][RoundKills]++;
			Player[killerid][TotalKills]++;
			Player[playerid][RoundDeaths]++;
			Player[playerid][TotalDeaths]++;

			new str[150];
			format(
				str, sizeof(str), "%s%s {FFFFFF}killed %s%s {FFFFFF}with %s [%.1f ft] [%d HP]", TextColor[Player[killerid][Team]], Player[killerid][Name],
				TextColor[Player[playerid][Team]], Player[playerid][Name], WeaponNames[reason], GetDistanceBetweenPlayers(killerid, playerid),
				(Player[killerid][pHealth] + Player[killerid][pArmour]));
			SendClientMessageToAll(-1, str);
			UpdateRoundKillDmgTDmg(killerid);

			OnPlayerAmmoUpdate(playerid);
		}
		else
		{
			if (Current == -1)
				SendDeathMessage(killerid, playerid, reason);
			if (Player[killerid][InDM])
			{
				SetHP(killerid, 100);
				SetAP(killerid, 100);

				Player[playerid][VWorld] = GetPlayerVirtualWorld(killerid);
			}
		}
	}
	if (Player[playerid][Playing])
	{
		new Float: x,
				   Float: y,
						  Float: z;
		GetPlayerPos(playerid, x, y, z);
		PlayersDead[Player[playerid][Team]]++;
		CreateDeadBody(playerid, killerid, reason, 0.0, x, y, z);
		PlayerNoLeadTeam(playerid);
		if (reason != WEAPON_KNIFE && DeathCamera) // if weapon is not knife and death camera system is not disabled
		{
			new bool: showdeathquote = true;
			if (KillerConnected)
				showdeathquote = !Player[killerid][HasDeathQuote];
			PlayDeathCamera(playerid, x, y, z, showdeathquote);
		}
		else // If not
			SetPreciseTimer("SpectateAnyPlayerT", 1000, false, "i", playerid);
		// Create an icon on radar where the player died
		CreateTeamDeathMapIcon(Player[playerid][Team], x, y, z);
	}
	else if (Player[playerid][InDuel])
		ProcessDuellerDeath(playerid, killerid, reason);

	// Hide arena out of bound warning textdraws if they're shown
	if (Player[playerid][OutOfArena] != MAX_ZONE_LIMIT_WARNINGS)
	{
		PlayerTextDrawHide(playerid, AreaCheckTD[playerid]);
		PlayerTextDrawHide(playerid, AreaCheckBG[playerid]);
	}
	Player[playerid][InDM]	  = false;
	Player[playerid][Playing] = false;
	Iter_Remove(PlayersInRound, playerid);
	UpdateTeamPlayerCount(Player[playerid][Team], true, playerid);
	UpdateTeamHP(Player[playerid][Team], playerid);
	// Handle spectate
	foreach (new i : AllSpectators)
	{
		if (Player[i][IsSpectatingID] == playerid)
		{
			if (Player[i][Team] == REFEREE)
				SpectateAnyPlayer(i, false, true, playerid);
			else
				SpectateAnyPlayer(i, true, true, playerid);
		}
	}

	// If they're selecting from gunmenu
	if (Player[playerid][OnGunmenu])
	{
		// Hide it!!!
		HidePlayerGunmenu(playerid);
	}

	// Reset player gunmenu selections
	ResetPlayerGunmenu(playerid, false);

	// Call OnPlayerLeaveCheckpoint to see if player was in CP and fix issues
	OnPlayerLeaveCheckpoint(playerid);

	// If he's spectating, stop it
	if (Player[playerid][Spectating])
		StopSpectate(playerid);

	if (!Player[playerid][InDeathCamera])
	{
		// If they're in a DM
		if (Player[playerid][DMReadd] > 0)
		{
			GetPlayerPos(playerid, Player[playerid][DmPosX], Player[playerid][DmPosY], Player[playerid][DmPosZ]);
			GetPlayerFacingAngle(playerid, Player[playerid][DmAngle]);
			// Re-spawn them there
			SpawnInDM(playerid, Player[playerid][DMReadd]);
		}
		else // Spawn player in a lobby
			SpawnInLobby(playerid);
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	// todo: test if this callback should be used under any weird circumstances. e.g: falling from a large cliff, exploding while driving a car, etc...

	if (Player[playerid][AlreadyDying])
		return 1; // Stop! Server-sided death system is already handling this.

	// case: died while driving a vehicle which exploded
	if (GetPlayerVehicleID(playerid) != 0)
	{
		ServerOnPlayerDeath(playerid, INVALID_PLAYER_ID, 51);
		return 1;
	}

	// case: died while diving with a parachute?
	if (reason == WEAPON_PARACHUTE)
	{
		ServerOnPlayerDeath(playerid, INVALID_PLAYER_ID, WEAPON_PARACHUTE);
		return 1;
	}

	// case: fell down
	if (reason == 54)
	{
		ServerOnPlayerDeath(playerid, INVALID_PLAYER_ID, 54);
		return 1;
	}

	// case: suicide
	if (reason == 255)
	{
		ServerOnPlayerDeath(playerid, INVALID_PLAYER_ID, 255);
		return 1;
	}

	// unknown cases
	SendClientMessageToAll(-1, va_return("DEBUG:Client:OnPlayerDeath(playerid:%d, killerid:%d, reason:%d)", playerid, killerid, reason));
	ServerOnPlayerDeath(playerid, killerid, reason);
	return 1;
}
