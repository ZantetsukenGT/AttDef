#if defined _attdef_OnPLeaveCheckpoint
	#endinput
#endif
#define _attdef_OnPLeaveCheckpoint

public OnPlayerLeaveCheckpoint(playerid)
{
	switch (GameType)
	{
		case BASE:
		{
			if (Player[playerid][Team] == ATTACKER && Player[playerid][WasInCP])
			{
				PlayersInCP--;
				Player[playerid][WasInCP] = false;
				if (PlayersInCP <= 0)
				{
					PlayersInCP	  = 0;
					CurrentCPTime = ConfigCPTime + 1;
					TextDrawHideForAll(EN_CheckPoint);
					TextDrawHideForAll(CheckpointWarningBox);
					TextDrawColor(timerCircleTD, 0x00000033);
					GangZoneStopFlashForAll(CPZone);
					foreach (new i : Player)
					{
						if (!Player[i][Spawned])
							continue;

						if (Player[i][RoundTDStyle] != 1)
							continue;

						TextDrawShowForPlayer(i, timerCircleTD);
					}
				}
				else
				{
					new cpstr[256];
					format(cpstr, sizeof cpstr, "~r~Players In CP");
					new ct = 0;
					foreach (new i : PlayersInRound)
					{
						if (Player[i][WasInCP])
						{
							ct++;
							format(cpstr, sizeof(cpstr), "%s~n~~r~- %s%s", cpstr, MAIN_TEXT_COLOUR, Player[i][Name]);
						}
					}
					if (ct != 0 || RecountPlayersOnCP() != 0) // if it stays 0 and PlayersInCP says it's more than 0 then something must be wrong
						TextDrawSetString(EN_CheckPoint, cpstr);
				}
			}
		}
		case ARENA:
		{
			if (Player[playerid][Team] == TeamCapturingCP && Player[playerid][WasInCP])
			{
				PlayersInCP--;
				Player[playerid][WasInCP] = false;
				if (PlayersInCP <= 0)
				{
					TeamCapturingCP = NON;
					PlayersInCP		= 0;
					CurrentCPTime	= ConfigCPTime + 1;
					TextDrawHideForAll(EN_CheckPoint);
					TextDrawColor(timerCircleTD, 0x00000033);
					foreach (new i : Player)
					{
						if (!Player[i][Spawned])
							continue;

						if (Player[i][RoundTDStyle] != 1)
							continue;

						TextDrawShowForPlayer(i, timerCircleTD);
					}
				}
				else
				{
					new cpstr[256];
					format(cpstr, sizeof cpstr, "%sPlayers In CP", TDC[Player[playerid][Team]]);
					new ct = 0;
					foreach (new i : PlayersInRound)
					{
						if (Player[i][WasInCP])
						{
							ct++;
							format(cpstr, sizeof(cpstr), "%s~n~%s- %s%s", cpstr, TDC[Player[i][Team]], MAIN_TEXT_COLOUR, Player[i][Name]);
						}
					}
					if (ct != 0 || RecountPlayersOnCP() != 0) // if it stays 0 and PlayersInCP says it's more than 0 then something must be wrong
						TextDrawSetString(EN_CheckPoint, cpstr);
				}
			}
		}
	}
	return 1;
}
