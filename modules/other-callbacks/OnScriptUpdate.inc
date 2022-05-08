#if defined _attdef_OnScriptUpdate
	#endinput
#endif
#define _attdef_OnScriptUpdate

// OnScriptUpdate - interval: 1000 ms
forward OnScriptUpdate();
public OnScriptUpdate()
{
	foreach (new i : Player)
	{
		// AFK Variable Update
		Player[i][PauseCount]++;

		// Update player FPS
		UpdatePlayerFPS(i);

		// Show target info
		ShowTargetInfo(i, GetPlayerTargetPlayer(i));

		// Update net info textdraws
		if (PlayerInterface[i][INTERFACE_NET])
		{
			new pFPS	   = GetPlayerFPS(i);
			new Float: pPL = NetStats_PacketLossPercent(i);
			new pPing	   = GetPlayerPing(i);
			PlayerTextDrawSetString(
				i, FPSPingPacket[i], va_return("%sFPS ~r~%d %sPing ~r~%d %sPacketLoss ~r~%.2f%%", MAIN_TEXT_COLOUR, pFPS, MAIN_TEXT_COLOUR, pPing, MAIN_TEXT_COLOUR, pPL));
			Update3DTextLabelText(
				Player[i][InfoLabel], -1,
				va_return(
					"%sPL: {FFFFFF}%.1f%%\n%sPing: {FFFFFF}%d\n%sFPS: {FFFFFF}%d", TextColor[Player[i][Team]], pPL, TextColor[Player[i][Team]], pPing, TextColor[Player[i][Team]],
					pFPS));
		}
	}

	// Update Vehicle Information
	if (VehicleHealthTextdraw)
	{
		foreach (new i : PlayersInVehicles)
		{
			new vID = GetPlayerVehicleID(i);
			if (vID) //race condition: if the player is indeed in a vehicle
			{
				new vModelID = GetVehicleModel(vID);
				if (vModelID) //race condition: does the vehicle still exist? this check is probably not needed
				{
					new Float: vHealth;
					GetVehicleHealth(vID, vHealth);
					PlayerTextDrawSetString(i, VInfo[i], va_return("~w~%s ~r~%.0f%%", aVehicleNames[vModelID - 400], vHealth / 10));
				}
			}
		}
	}
	return 1;
}
