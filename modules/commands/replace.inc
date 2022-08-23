#if defined _attdef_cmd_replace
	#endinput
#endif
#define _attdef_cmd_replace

YCMD: replace(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "replace players whether they're connected to the server or not.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");

	LogAdminCommand("replace", playerid, INVALID_PLAYER_ID);

	foreach (new i : Player)
	{
		if (Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
			continue;

		AddDialogListitem(playerid, Player[i][Name]);
	}
	ShowPlayerDialogPages(playerid, #ReplaceFirstDialog, DIALOG_STYLE_LIST, COL_PRIM "Player to add", "Process", "Cancel", 15);
	return 1;
}

DialogPages:ReplaceFirstDialog(playerid, response, listitem, inputtext[])
{
	if (!response)
		return 1;
	new ToAddID = -1;
	foreach (new i : Player)
	{
		if (!strcmp(Player[i][Name], inputtext, false, strlen(inputtext)))
		{
			ToAddID++;
			REPLACE_ToAddID[playerid] = i;
			break;
		}
	}
	if (ToAddID > -1)
	{
		foreach (new i : Player)
		{
			if (!Player[i][Playing])
				continue;

			AddDialogListitem(playerid, Player[i][Name]);
		}
		for (new i = 0; i < SAVE_SLOTS; i++)
		{
			if (SaveVariables[i][pName][0] && SaveVariables[i][RoundID] == Current && SaveVariables[i][ToBeAdded] == true)
			{
				AddDialogListitem(playerid, SaveVariables[i][pName]);
			}
		}
		ShowPlayerDialogPages(playerid, #ReplaceSecondDialog, DIALOG_STYLE_LIST, COL_PRIM "Player to replace", "Process", "Cancel", 15);
	}
	else
		SendErrorMessage(playerid, "Player not found.");
	return 1;
}

DialogPages:ReplaceSecondDialog(playerid, response, listitem, inputtext[])
{
	if (!response)
		return 1;
	new ToReplaceID = -1;
	foreach (new i : Player)
	{
		if (!strcmp(Player[i][Name], inputtext, false, strlen(inputtext)))
		{
			ToReplaceID = i;
			break;
		}
	}
	if (ToReplaceID != -1)
	{
		new ToAddID = REPLACE_ToAddID[playerid];
		if (!IsPlayerConnected(ToAddID))
		{
			return SendErrorMessage(playerid, "Player is not connected anymore.");
		}

		if (Player[ToAddID][InDM] == true)
		{
			Player[ToAddID][InDM]	 = false;
			Player[ToAddID][DMReadd] = 0;
		}

		if (Player[ToAddID][InDuel] == true)
			return SendErrorMessage(playerid, "That player is in a duel."); //duel

		if (Player[ToAddID][LastVehicle])
		{
			foreach (new i : VehicleOccupant(Player[ToAddID][LastVehicle]))
			{
				RemovePlayerFromVehicle(i);
			}
			DestroyVehicle(Player[ToAddID][LastVehicle]);
			Player[ToAddID][LastVehicle] = 0;
		}

		if (Player[ToAddID][Spectating] == true)
			StopSpectate(ToAddID);

		SetTimerEx("OnPlayerReplace", 500, false, "iii", ToAddID, ToReplaceID, playerid);
	}
	else
	{
		for (new i = 0; i < SAVE_SLOTS; i++)
		{
			if (SaveVariables[i][pName][0] && !strcmp(SaveVariables[i][pName], inputtext, false, strlen(inputtext)) && SaveVariables[i][RoundID] == Current)
			{
				ToReplaceID = i;
				break;
			}
		}
		if (ToReplaceID > -1)
		{
			new ToAddID = REPLACE_ToAddID[playerid];
			if (!IsPlayerConnected(ToAddID))
			{
				return SendErrorMessage(playerid, "Player is not connected anymore.");
			}

			if (Player[ToAddID][InDM] == true)
			{
				Player[ToAddID][InDM]	 = false;
				Player[ToAddID][DMReadd] = 0;
			}

			if (Player[ToAddID][InDuel] == true)
				return SendErrorMessage(playerid, "That player is in a duel."); //duel

			if (Player[ToAddID][LastVehicle])
			{
				foreach (new i : VehicleOccupant(Player[ToAddID][LastVehicle]))
				{
					RemovePlayerFromVehicle(i);
				}
				DestroyVehicle(Player[ToAddID][LastVehicle]);
				Player[ToAddID][LastVehicle] = 0;
			}

			if (Player[ToAddID][Spectating] == true)
				StopSpectate(ToAddID);
			SetTimerEx("OnPlayerInGameReplace", 500, false, "iii", ToAddID, ToReplaceID, playerid);
		}
		else
			SendErrorMessage(playerid, "Player not found.");
	}
	return 1;
}
