#if defined _attdef_OnScriptUpdate
	#endinput
#endif
#define _attdef_OnScriptUpdate

// OnScriptUpdate - interval: 1000 ms
forward OnScriptUpdate();
public OnScriptUpdate()
{
	CheckVisualDamageTextDraws(); // This basically hides damage textdraws and damage bubbles that should be hidden

	foreach (new i : Player)
	{
		// AFK Variable Update
		Player[i][PauseCount]++;

		// Get & update player FPS
		GetPlayerFPS(i);

		// Show target info
		ShowTargetInfo(i, GetPlayerTargetPlayer(i));

		// Update net info textdraws
		if (PlayerInterface[i][INTERFACE_NET])
		{
			PlayerTextDrawSetString(
				i, FPSPingPacket[i],
				va_return(
					"%sFPS ~r~%d %sPing ~r~%d %sPacketLoss ~r~%.2f%%", MAIN_TEXT_COLOUR, Player[i][FPS], MAIN_TEXT_COLOUR, GetPlayerPing(i), MAIN_TEXT_COLOUR,
					NetStats_PacketLossPercent(i)));
			Update3DTextLabelText(
				Player[i][InfoLabel], -1,
				va_return(
					"%sPL: {FFFFFF}%.1f%%\n%sPing: {FFFFFF}%d\n%sFPS: {FFFFFF}%d", TextColor[Player[i][Team]], NetStats_PacketLossPercent(i), TextColor[Player[i][Team]],
					GetPlayerPing(i), TextColor[Player[i][Team]], Player[i][FPS]));
		}
	}

	// Update Vehicle Information
	if (VehicleHealthTextdraw)
	{
		foreach (new i : PlayersInVehicles)
		{
			new vID, Float: vHealth;
			vID = GetPlayerVehicleID(i);
			GetVehicleHealth(vID, vHealth);
			PlayerTextDrawSetString(i, VInfo[i], va_return("~w~%s ~r~%.0f%%", aVehicleNames[GetVehicleModel(vID) - 400], vHealth / 10));
		}
	}

	return 1;
}
