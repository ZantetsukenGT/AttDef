#if defined _attdef_OnPClickTD
	#endinput
#endif
#define _attdef_OnPClickTD

public OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (clickedid == Text: INVALID_TEXT_DRAW)
	{
		if (PlayerOnInterface { playerid } == true)
		{
			DisableMatchInterface(playerid);
			return 1;
		}
		return 1;
	}

	if (clickedid == WarModeText)
	{
		if (Current != -1)
			return SendErrorMessage(playerid, "Can't use this option while round is on.");

		if (WarMode == false)
		{
			MatchRoundsStarted = 0;
			for (new i = 0; i < 101; i++)
			{
				MatchRoundsRecord[i][round__ID]		   = -1;
				MatchRoundsRecord[i][round__type]	   = -1;
				MatchRoundsRecord[i][round__completed] = false;
			}

			foreach (new i : Player)
			{
				Player[i][TotalKills]		 = 0;
				Player[i][TotalDeaths]		 = 0;
				Player[i][TotalDamage]		 = 0.0;
				Player[i][RoundPlayed]		 = 0;
				Player[i][TotalBulletsFired] = 0;
				Player[i][TotalshotsHit]	 = 0;
			}
			ShowPlayerDialog(
				playerid, DIALOG_ATT_NAME, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Name", "" COL_PRIM "Enter {FFFFFF}Attacker " COL_PRIM "Team Name Below:", "Next",
				"Close");
		}
		else
		{
			ShowPlayerDialog(playerid, DIALOG_WAR_RESET, DIALOG_STYLE_MSGBOX, "" COL_PRIM "War Dialog", "" COL_PRIM "Are you sure you want to turn War Mode off?", "Yes", "No");
		}

		return 1;
	}

	if (clickedid == LockServerTD)
	{
		if (!ServerLocked)
		{
			ShowPlayerDialog(playerid, DIALOG_SERVER_PASS, DIALOG_STYLE_INPUT, "" COL_PRIM "Server Password", "" COL_PRIM "Enter server password below:", "Ok", "Close");
		}
		else
		{
			SendRconCommand("password 0");
			SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has unlocked the server.", Player[playerid][Name]));
			TextDrawSetString(LockServerTD, va_return("%sServer: ~r~Unlocked", MAIN_TEXT_COLOUR));

			ServerLocked = false;
			PermLocked	 = false;
		}
		return 1;
	}

	if (clickedid == CloseText)
	{
		DisableMatchInterface(playerid);
		return 1;
	}
	return 0;
}
