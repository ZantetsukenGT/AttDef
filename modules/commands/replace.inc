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

	DynDialog_Clear(playerid);
	foreach (new i : Player)
	{
		if (Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
			continue;

		DynDialog_AddItem(playerid, i, Player[i][Name]);
	}
	DynDialog_Show(playerid, using public ReplaceFirstDialog<iiiis>, DIALOG_STYLE_LIST, COL_PRIM "Player to add", "Process", "Cancel", 15);
	return 1;
}

hook ReplaceFirstDialog(playerid, response, additional_data, listitem, string: inputtext[])
{
	DynDialog_Clear(playerid);
	if (!response)
		return 1;
	
	REPLACE_ToAddID[playerid] = additional_data;
	foreach (new i : Player)
	{
		if (!Player[i][Playing])
			continue;

		DynDialog_AddItem(playerid, i, Player[i][Name]); // additional_data = playerid = [0, MAX_PLAYERS - 1] for online players
	}
	for (new i = 0; i < SAVE_SLOTS; i++)
	{
		if (SaveVariables[i][pName][0] && SaveVariables[i][RoundID] == Current && SaveVariables[i][ToBeAdded] == true)
		{
			DynDialog_AddItem(playerid, -i - 1, SaveVariables[i][pName]); // additional_data = -slot - 1 = [-SAVE_SLOTS, -1] for offline players
		}
	}
	DynDialog_Show(playerid, using public ReplaceSecondDialog<iiiis>, DIALOG_STYLE_LIST, COL_PRIM "Player to replace", "Process", "Cancel", 15);
	return 1;
}

hook ReplaceSecondDialog(playerid, response, additional_data, listitem, string: inputtext[])
{
	DynDialog_Clear(playerid);
	if (!response)
		return 1;
	new ToReplaceID = additional_data;
	if (ToReplaceID >= 0)
	{
		new ToAddID = REPLACE_ToAddID[playerid];
		if (!IsPlayerConnected(ToAddID))
			return SendErrorMessage(playerid, "Player is not connected anymore.");

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
		ToReplaceID = -ToReplaceID - 1; // reversing the transformation we did to the additional_data
		new ToAddID = REPLACE_ToAddID[playerid];
		if (!IsPlayerConnected(ToAddID))
			return SendErrorMessage(playerid, "Player is not connected anymore.");

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
	return 1;
}
