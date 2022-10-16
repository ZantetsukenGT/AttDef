#if defined _attdef_cmd_afk
	#endinput
#endif
#define _attdef_cmd_afk

YCMD: afk(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "switch to AFK mode.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "You cannot switch to AFK mode while playing");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel. Use /rq first");
	if (Player[playerid][Spectating])
		StopSpectate(playerid);
	if (Player[playerid][InDM])
		QuitDM(playerid);

	Player[playerid][Team] = NON;
	Player[playerid][IsAFK] = true;
	
	SetPlayerColor(playerid, 0xAAAAAAAA);
	TogglePlayerControllable(playerid, 0);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set himself to AFK mode.", Player[playerid][Name]);
}
