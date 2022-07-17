#if defined _attdef_OnPDeath
	#endinput
#endif
#define _attdef_OnPDeath

public OnPlayerDeath(playerid, killerid, reason)
{
	new KillerConnected = IsPlayerConnected(killerid);
	if (!KillerConnected)
	{
		if (Player[playerid][Playing])
		{
			SendDeathMessage(INVALID_PLAYER_ID, playerid, reason);
			Player[playerid][RoundDeaths]++;
			Player[playerid][TotalDeaths]++;

			va_SendClientMessageToAll(-1, "%s%s {FFFFFF}has died by: {FFFFFF}%s", TextColor[Player[playerid][Team]], Player[playerid][Name], ReturnWeaponName(reason));
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
			va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "%sKilled By: ~r~%s", MAIN_TEXT_COLOUR, Player[killerid][Name]);
			va_PlayerTextDrawSetString(killerid, DeathText[killerid][0], "%sYou Killed: ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]);
		}
		else
		{
			switch (reason)
			{
				case WEAPON_KNIFE:
				{
					va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "~rp~%s%s knifed you", Player[killerid][Name], MAIN_TEXT_COLOUR);
					va_PlayerTextDrawSetString(killerid, DeathText[killerid][0], "%sYou knifed ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]);
				}
				case WEAPON_GRENADE:
				{
					va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "~r~%s%s bombed you", Player[killerid][Name], MAIN_TEXT_COLOUR);
					va_PlayerTextDrawSetString(killerid, DeathText[killerid][0], "%sYou bombed ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]);
				}
				default:
				{
					switch (random(4))
					{
						case 0:
						{
							va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "~r~%s%s raped you", Player[killerid][Name], MAIN_TEXT_COLOUR);
							va_PlayerTextDrawSetString(killerid, DeathText[killerid][0], "%sYou raped ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]);
						}
						case 1:
						{
							va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "~r~%s%s owned you", Player[killerid][Name], MAIN_TEXT_COLOUR);
							va_PlayerTextDrawSetString(killerid, DeathText[killerid][0], "%sYou owned ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]);
						}
						case 2:
						{
							va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "~r~%s%s murdered you", Player[killerid][Name], MAIN_TEXT_COLOUR);
							va_PlayerTextDrawSetString(killerid, DeathText[killerid][0], "%sYou murdered ~r~%s", MAIN_TEXT_COLOUR, Player[playerid][Name]);
						}
						case 3:
						{
							va_PlayerTextDrawSetString(playerid, DeathText[playerid][1], "~r~%s%s sent you to cemetery", Player[killerid][Name], MAIN_TEXT_COLOUR);
							va_PlayerTextDrawSetString(
								killerid, DeathText[killerid][0], "%sYou sent ~r~%s%s to cemetery", MAIN_TEXT_COLOUR, Player[playerid][Name], MAIN_TEXT_COLOUR);
						}
					}
				}
			}
		}

		PlayerTextDrawShow(killerid, DeathText[killerid][0]);
		PlayerTextDrawShow(playerid, DeathText[playerid][1]);

		SetTimerEx("DeathMessageF", 4000, false, "ii", killerid, playerid);

		if (Player[playerid][Playing] && Player[killerid][Playing] && AllowStartBase)
		{
			ShowPlayerDeathMessage(killerid, playerid);
			SendDeathMessage(killerid, playerid, reason);

			Player[killerid][RoundKills]++;
			Player[killerid][TotalKills]++;
			Player[playerid][RoundDeaths]++;
			Player[playerid][TotalDeaths]++;

			va_SendClientMessageToAll(
				-1, "%s%s {FFFFFF}killed %s%s {FFFFFF}with %s [%.1f ft] [%.1f HP]", TextColor[Player[killerid][Team]], Player[killerid][Name], TextColor[Player[playerid][Team]],
				Player[playerid][Name], ReturnWeaponName(reason), GetDistanceBetweenPlayers(killerid, playerid), GetPlayerHealth(killerid) + GetPlayerArmour(killerid));
			UpdateRoundKillDmgTDmg(killerid);

			OnPlayerAmmoUpdate(playerid);
		}
		else
		{
			if (Current == -1)
				SendDeathMessage(killerid, playerid, reason);
			if (Player[killerid][InDM])
			{
				SetHP(killerid, 100.0);
				SetAP(killerid, 100.0);

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
		Player[playerid][CouldShowDeathQuote] = reason != WEAPON_KNIFE && DeathCamera;
		if (Player[playerid][CouldShowDeathQuote]) // if reason is not knife and death camera system is not disabled
		{
			Player[playerid][ShowDeathQuote] = KillerConnected ? !Player[killerid][HasDeathQuote] : true;
		}
		// Create an icon on radar where the player died
		CreateTeamDeathMapIcon(Player[playerid][Team], x, y, z);
	}
	return 1;
}
