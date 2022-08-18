#if defined _attdef_OnPStateChange
	#endinput
#endif
#define _attdef_OnPStateChange

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	switch (newstate)
	{
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
		{
			if (Player[playerid][Team] == DEFENDER && Player[playerid][Playing] && !DefendersWithVehicles)
			{
				new Float: defPos[3];
				GetPlayerPos(playerid, defPos[0], defPos[1], defPos[2]);
				SetPlayerPos(playerid, defPos[0] + 1.0, defPos[1] + 1.0, defPos[2] + 1.0);
				return 1;
			}
			SetPlayerArmedWeapon(playerid, 0);

			if (Player[playerid][Playing] && Player[playerid][WasInCP])
			{
				if (IsPlayerInRangeOfPoint(playerid, 2.0, BCPSpawn[Current][0], BCPSpawn[Current][1], BCPSpawn[Current][2]))
					CallLocalFunction("OnPlayerLeaveCheckpoint", "i", playerid);
			}

			if (Player[playerid][BeingSpeced])
			{
				foreach (new i : PlayerSpectators[playerid])
				{
					TogglePlayerSpectating(i, 1);
					PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
				}
			}

			if (VehicleHealthTextdraw)
			{
				PlayerTextDrawSetString(playerid, VInfo[playerid], "_");
				PlayerTextDrawShow(playerid, VInfo[playerid]);
			}
			Iter_Add(PlayersInVehicles, playerid);
		}
		case PLAYER_STATE_ONFOOT:
		{
			switch (oldstate)
			{
				case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
				{
					if (Player[playerid][Team] == ATTACKER && Player[playerid][Playing])
					{
						if (IsPlayerInRangeOfPoint(playerid, 2.0, BCPSpawn[Current][0], BCPSpawn[Current][1], BCPSpawn[Current][2]))
							CallLocalFunction("OnPlayerEnterCheckpoint", "i", playerid);
					}
					if (Player[playerid][BeingSpeced])
					{
						foreach (new i : PlayerSpectators[playerid])
						{
							TogglePlayerSpectating(i, 1);
							PlayerSpectatePlayer(i, playerid);
						}
					}
				}
			}
		}
	}
	
	switch (oldstate)
	{
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
		{
			if (VehicleHealthTextdraw)
				PlayerTextDrawHide(playerid, VInfo[playerid]);
			Iter_Remove(PlayersInVehicles, playerid);
		}
	}
	return 1;
}
