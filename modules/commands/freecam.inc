#if defined _attdef_cmd_freecam
	#endinput
#endif
#define _attdef_cmd_freecam

YCMD: freecam(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "free your camera so you can move freely. (Useful in movie-making?)");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (GetPlayerVehicleID(playerid))
		return SendErrorMessage(playerid, "You cannot use this command while in vehicle.");
	if (Player[playerid][Playing] || Player[playerid][InDM] || Player[playerid][Spectating] && !noclipdata[playerid][FlyMode])
		return 1;

	if (noclipdata[playerid][FlyMode])
		return SendClientMessage(playerid, -1, "Use /specoff to exit FreeCam!");

	PlayerFlyMode(playerid, false);
	PlayerTextDrawHide(playerid, RoundKillDmgTDmg[playerid]);
	PlayerTextDrawHide(playerid, FPSPingPacket[playerid]);
	PlayerTextDrawHide(playerid, BaseID_VS[playerid]);
	return SendClientMessage(playerid, -1, "Use /specoff to exit FreeCam! Try /movecam for camera movement");
}
