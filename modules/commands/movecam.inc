#if defined _attdef_cmd_movecam
	#endinput
#endif
#define _attdef_cmd_movecam

YCMD: movecam(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "move your camera to a player when you're in /freecam mode");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command while playing.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (!noclipdata[playerid][FlyMode])
		return SendErrorMessage(playerid, "You have to be in freecam mode, type /freecam");
	if (Player[playerid][Team] != REFEREE)
		return SendErrorMessage(playerid, "You must be in referee team to use this command");
	if (isnull(params))
		return SendUsageMessage(playerid, "/movecam [to playerid]");

	new toplayerid = strval(params);
	if (!IsPlayerConnected(toplayerid) || IsPlayerNPC(toplayerid))
		return SendErrorMessage(playerid, "Invalid player ID");

	SetPlayerInterior(playerid, GetPlayerInterior(toplayerid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(toplayerid));

	new Float: x,
		Float: y,
		Float: z;
	GetPlayerPos(toplayerid, x, y, z);
	SetFreeCamPos(playerid, x, y, z);
	return 1;
}
