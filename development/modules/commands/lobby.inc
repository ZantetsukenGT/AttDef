#if defined _attdef_cmd_lobby
	#endinput
#endif
#define _attdef_cmd_lobby

YCMD: lobby(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "teleport you to the lobby.");
	if (Player[playerid][InDM])
		QuitDM(playerid);
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel. Use /rq instead.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Cannot go to lobby while you're playing. Use /rem maybe?");

	SpawnInLobby(playerid);
	return 1;
}
