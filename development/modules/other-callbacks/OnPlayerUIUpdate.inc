#if defined _attdef_OnPUIUpdate
	#endinput
#endif
#define _attdef_OnPUIUpdate

// OnPlayerUIUpdate - interval: 1000 ms
ptask OnPlayerUIUpdate[1000](playerid)
{
	// AFK Variable Update
	Player[playerid][PauseCount]++;

	// This basically hides damage bubbles that should be hidden
	//UpdateDamageBubbles(playerid);

	// Show target info
	ShowTargetInfo(playerid, GetPlayerTargetPlayer(playerid));

	// Update net info textdraws
	if (PlayerInterface[playerid][INTERFACE_NET])
	{
		new pFPS	   = GetPlayerFPS(playerid);
		new Float: pPL = NetStats_PacketLossPercent(playerid);
		new pPing	   = GetPlayerPing(playerid);
		PlayerTextDrawSetString(
			playerid, FPSPingPacket[playerid],
			"%sFPS ~r~%d %sPing ~r~%d %sPacketLoss ~r~%.2f%%", MAIN_TEXT_COLOUR, pFPS, MAIN_TEXT_COLOUR, pPing, MAIN_TEXT_COLOUR, pPL);
		Update3DTextLabelText(
			Player[playerid][InfoLabel], -1,
			"%sPL: {FFFFFF}%.1f%%\n%sPing: {FFFFFF}%d\n%sFPS: {FFFFFF}%d", TextColor[Player[playerid][Team]], pPL, TextColor[Player[playerid][Team]],
			pPing, TextColor[Player[playerid][Team]], pFPS);
	}
}
