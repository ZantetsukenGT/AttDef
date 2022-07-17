#if defined _attdef_OnScriptUpdate
	#endinput
#endif
#define _attdef_OnScriptUpdate

// OnScriptUpdate - interval: 1000 ms
ptask NetStatUpdate[1000](playerid)
{
	// AFK Variable Update
	Player[playerid][PauseCount]++;

	// Update player FPS
	UpdatePlayerFPS(playerid);

	// Show target info
	ShowTargetInfo(playerid, GetPlayerTargetPlayer(playerid));

	// Update net info textdraws
	if (PlayerInterface[playerid][INTERFACE_NET])
	{
		new pFPS	   = GetPlayerFPS(playerid);
		new Float: pPL = NetStats_PacketLossPercent(playerid);
		new pPing	   = GetPlayerPing(playerid);
		va_PlayerTextDrawSetString(
			playerid, FPSPingPacket[playerid], "%sFPS ~r~%d %sPing ~r~%d %sPacketLoss ~r~%.2f%%", MAIN_TEXT_COLOUR, pFPS, MAIN_TEXT_COLOUR, pPing, MAIN_TEXT_COLOUR, pPL);
		Update3DTextLabelText(
			Player[playerid][InfoLabel], -1,
			va_return(
				"%sPL: {FFFFFF}%.1f%%\n%sPing: {FFFFFF}%d\n%sFPS: {FFFFFF}%d", TextColor[Player[playerid][Team]], pPL, TextColor[Player[playerid][Team]], pPing, TextColor[Player[playerid][Team]],
				pFPS));

	}
}

task VehicleHealthUpdate[1000]()
{
	// Update Vehicle Information
	if (VehicleHealthTextdraw)
	{
		foreach (new i : PlayersInVehicles)
		{
			new vID = GetPlayerVehicleID(i),
				vModelID = GetVehicleModel(vID);
			if (vModelID) // without this check, there's potential array oob access
			{
				new Float: vHealth;
				GetVehicleHealth(vID, vHealth);
				va_PlayerTextDrawSetString(i, VInfo[i], "~w~%s ~r~%d%%", aVehicleNames[vModelID - 400], floatround(vHealth / 10));
			}
		}
	}
}
